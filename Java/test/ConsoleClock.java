package com.test;

import java.util.Date;
import java.util.concurrent.TimeUnit;

public class ConsoleClock implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            System.out.printf("%s\n", new Date());
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                System.out.printf("The FileClock has been interrupted");
            }
        }
    }

    public static void main(String[] args) {
        ConsoleClock clock = new ConsoleClock();
        Thread thread = new Thread(clock);

        // Starts the Thread
        thread.start();
        try {
            // Waits five seconds
            TimeUnit.SECONDS.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Interrupts the Thread
        thread.interrupt();
    }
}
