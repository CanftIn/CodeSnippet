package com.test;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

public class Videoconference implements Runnable {

    private final CountDownLatch controller;

    public Videoconference(int number) {
        controller = new CountDownLatch(number);
    }

    public void arrive(String name) {
        System.out.printf("%s has arrived.\n", name);
        controller.countDown();
        System.out.printf("VideoConference: Waiting for %d participants.\n", controller.getCount());
    }

    @Override
    public void run() {
        System.out.printf("VideoConference: Initialization: %d participants.\n", controller.getCount());
        try {
            // Wait for all the participants
            controller.await();
            // Starts the conference
            System.out.printf("VideoConference: All the participants have come\n");
            System.out.printf("VideoConference: Let's start...\n");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        // Creates a VideoConference with 10 participants.
        Videoconference conference = new Videoconference(10);
        // Creates a thread to run the VideoConference and start it.
        Thread threadConference = new Thread(conference);
        threadConference.start();

        // Creates ten participants, a thread for each one and starts them
        for (int i = 0; i < 10; i++) {
            Participant p = new Participant(conference, "Participant " + i);
            Thread t = new Thread(p);
            t.start();
        }

    }
}

class Participant implements Runnable {
    private Videoconference conference;
    private String name;

    public Participant(Videoconference conference, String name) {
        this.conference = conference;
        this.name = name;
    }

    @Override
    public void run() {
        Long duration = (long) (Math.random() * 10);
        try {
            TimeUnit.SECONDS.sleep(duration);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        conference.arrive(name);

    }
}