package com.company;

import java.time.LocalDate;

public class Calendar {

    public static void main(String[] args) {
        LocalDate lDate = LocalDate.now();
        int today = lDate.getDayOfMonth();

        lDate = lDate.minusDays(today - 1);
        int value = lDate.getDayOfWeek().getValue();

        System.out.println("Mon Tue Wed Thu Fri Sat Sun");
        for (int i = 0; i < value - 1; ++i)
            System.out.printf("   ");
        while (lDate.getMonthValue() == LocalDate.now().getMonthValue()) {
            System.out.printf("%3d", lDate.getDayOfMonth());
            lDate = lDate.plusDays(1);
            if (lDate.getDayOfWeek().getValue() == 1)
                System.out.println();
        }
    }
}
