package com.canftin;

public class Student extends Person {

    private int score;

    public Student(String name, int score) {
        super(name);
        this.score = score;
    }

    public int getScore() {
        return score;
    }


    @Override
    public String getDescription() {
        return "Student score: " + score;
    }
}
