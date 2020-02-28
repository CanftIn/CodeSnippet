package com.test;

import javafx.event.Event;

import java.util.Date;
import java.util.Deque;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.concurrent.TimeUnit;

public class WriterTask implements Runnable {
    Deque<MyEvent> deque;

    public WriterTask(Deque<MyEvent> deque) {
        this.deque = deque;
    }

    @Override
    public void run() {
        for (int i = 1; i < 100; i++) {
            // Creates and initializes the Event objects
            MyEvent event = new MyEvent();
            event.setDate(new Date());
            event.setEvent(
                    String.format("The thread %s has generated the event %d event", Thread.currentThread().getId(), i));

            // Add to the data structure
            deque.addFirst(event);
            try {
                // Sleeps during one second
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {

        // Creates the Event data structure
        Deque<MyEvent> deque = new ConcurrentLinkedDeque<>();

        // Creates the three WriterTask and starts them
        WriterTask writer = new WriterTask(deque);
        for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {
            Thread thread = new Thread(writer);
            thread.start();
        }

        // Creates a cleaner task and starts them
        CleanerTask cleaner = new CleanerTask(deque);
        cleaner.start();

    }
}

class CleanerTask extends Thread {
    private Deque<MyEvent> deque;

    public CleanerTask(Deque<MyEvent> deque) {
        this.deque = deque;
        // Establish that this is a Daemon Thread
        setDaemon(true);
    }

    @Override
    public void run() {
        while (true) {
            Date date = new Date();
            clean(date);
        }
    }

    private void clean(Date date) {
        long difference;
        boolean delete;
        if (deque.size() == 0) {
            return;
        }

        delete = false;
        do {
            MyEvent e = deque.getLast();
            difference = date.getTime() - e.getDate().getTime();
            if (difference > 10000) {
                System.out.printf("Cleaner: %s\n", e.getEvent());
                deque.removeLast();
                delete = true;
            }
        } while (difference > 10000);

        if (delete) {
            System.out.printf("Cleaner: Size of the queue: %d\n", deque.size());
        }
    }
}

class MyEvent {

    private Date date;

    private String event;

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getEvent() {
        return event;
    }

    public void setEvent(String event) {
        this.event = event;
    }
}