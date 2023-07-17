package com.test;

import java.text.CharacterIterator;
import java.text.StringCharacterIterator;

public class Test {
    public static void main(String[] args) throws NoSuchMethodException {
        String methodName = "fun";

        if (Test.class.getMethod("foo").getReturnType() == Void.TYPE) {
            System.out.println(methodName + "方法的返回值为void");
        } else {
            System.out.println(methodName + "方法的返回值不为void");
        }

        CharacterIterator it = new StringCharacterIterator("中国China");

        // 顺序遍历字符串"中国China"
        for (char c = it.first(); c != CharacterIterator.DONE; c = it.next()) {
            System.out.print(c + " ");
        }
        System.out.println();

        System.out.println("-----------------------------------------------------------");

        // 逆序遍历字符串"中国China"
        for (char c = it.last(); c != CharacterIterator.DONE; c = it.previous()) {
            System.out.print(c + " ");
        }
        System.out.println();
    }

    public void foo() {
    }
}