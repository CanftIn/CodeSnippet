package com.test;

public class Calculator extends Thread {

    @Override
    public void run() {
        long number = 1L;

        // This bucle never ends... until is interrupted
        while (true) {
            if (isPrime(number)) {
                System.out.printf("Number %d is Prime\n", number);
            }

            // When is interrupted, write a message and ends
            if (isInterrupted()) {
                System.out.printf("The Prime Generator has been Interrupted\n");
                return;
            }
            number++;
        }
    }

    private boolean isPrime(long number) {
        if (number <= 2) {
            return true;
        }
        for (long i = 2; i < number; i++) {
            if ((number % i) == 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Thread task = new Calculator();
        task.start();
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        task.interrupt();
        System.out.printf("Main: Status of the Thread: %s\n",
                task.getState());
        System.out.printf("Main: isInterrupted: %s\n",
                task.isInterrupted());
        System.out.printf("Main: isAlive: %s\n", task.isAlive());
    }
}
