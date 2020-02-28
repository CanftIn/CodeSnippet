package com.test;

import java.util.Date;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class PrintQueue {
    /**
     * Semaphore to control the access to the printers
     */
    private final Semaphore semaphore;

    /**
     * Array to control what printer is free
     */
    private final boolean freePrinters[];

    /**
     * Lock to control the access to the freePrinters array
     */
    private final Lock lockPrinters;

    /**
     * Constructor of the class. It initializes the three objects
     */
    public PrintQueue() {
        semaphore = new Semaphore(3);
        freePrinters = new boolean[3];
        for (int i = 0; i < 3; i++) {
            freePrinters[i] = true;
        }
        lockPrinters = new ReentrantLock();
    }

    public void printJob(Object document) {
        try {
            // Get access to the semaphore. If there is one or more printers free,
            // it will get the access to one of the printers
            semaphore.acquire();

            // Get the number of the free printer
            int assignedPrinter = getPrinter();

            Long duration = (long) (Math.random() * 10);
            System.out.printf("%s - %s: PrintQueue: Printing a Job in Printer %d during %d seconds\n", new Date(), Thread.currentThread().getName(), assignedPrinter, duration);
            TimeUnit.SECONDS.sleep(duration);

            // Free the printer
            freePrinters[assignedPrinter] = true;
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            // Free the semaphore
            semaphore.release();
        }
    }

    private int getPrinter() {
        int ret = -1;

        try {
            // Get the access to the array
            lockPrinters.lock();
            // Look for the first free printer
            for (int i = 0; i < freePrinters.length; i++) {
                if (freePrinters[i]) {
                    ret = i;
                    freePrinters[i] = false;
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Free the access to the array
            lockPrinters.unlock();
        }
        return ret;
    }

    public static void main(String args[]) {

        // Creates the print queue
        PrintQueue printQueue = new PrintQueue();

        // Creates twelve Threads
        Thread[] threads = new Thread[12];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new Job(printQueue), "Thread " + i);
        }

        // Starts the Threads
        for (int i = 0; i < threads.length; i++) {
            threads[i].start();
        }
    }
}

class Job implements Runnable {

    /**
     * Queue to print the documents
     */
    private PrintQueue printQueue;

    /**
     * Constructor of the class. Initializes the queue
     *
     * @param printQueue
     */
    public Job(PrintQueue printQueue) {
        this.printQueue = printQueue;
    }

    /**
     * Core method of the Job. Sends the document to the print queue and waits
     * for its finalization
     */
    @Override
    public void run() {
        System.out.printf("%s: Going to print a job\n", Thread.currentThread().getName());
        printQueue.printJob(new Object());
        System.out.printf("%s: The document has been printed\n", Thread.currentThread().getName());
    }
}