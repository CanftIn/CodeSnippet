package com.test;

public class Thread3 extends Thread {
    volatile boolean stop = false;

    public void run() {
        while (!stop) {
            System.out.println("Thread running...");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                // 接收到一个中断异常（InterruptedException），从而提早地终结被阻塞状态
                System.out.println("Thread interrupted...");
            }
        }
        System.out.println("Thread exiting under request...");
    }

    public static void main(String[] args) throws InterruptedException {
        Thread3 t = new Thread3();
        t.start();
        Thread.sleep(3000);
        t.stop = true;
        t.interrupt();
    }
}