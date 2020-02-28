package com.canftin;

import java.util.*;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class CollectionTest<E> {

    public static void main(String[] args) {
//        Collection c1 = new ArrayList();
//        c1.add("fuck");
//        c1.add("shit");
//        System.out.println(c1);
//        Collection c2 = new ArrayList();
//        c2.add("cao");
//        c2.addAll(c1);
//        System.out.println(c2);
//        c2.remove("fuck");
//        System.out.println(c2);
//        Object[] strarr = c2.toArray();
//        for(Object a : strarr)
//        {
//            System.out.println(a);
//        }
//        AbstractCollection c = new ArrayList();
//        c.add("fuck");
//        c.add("shit");
//        System.out.println(c);
//        String s = c.toString();
//        System.out.println(s);
        List<String> arrs = new ArrayList<>();
        arrs.add("a");
        arrs.add("b");
        arrs.add("c");
        arrs.add("d");
        arrs.add("e");
        arrs.add("f");
        arrs.add("h");
        arrs.add("i");
        arrs.add("j");
        Spliterator<String> a = arrs.spliterator();
        //此时结果：a:0-9（index-fence）
        Spliterator<String> b = a.trySplit();
        //此时结果：b:4-9,a:0-4
        Spliterator<String> c = a.trySplit();
        //此时结果：c:4-6,b:4-9,a:6-9
        Spliterator<String> d = a.trySplit();
        //此时结果：d:6-7,c:4-6,b:4-9,a:7-9

        String arr = "12%3 21sdas s34d dfsdz45   R3 jo34 sjkf8 3$1P 213ikflsd fdg55 kfd";
        Stream<Character> stream = IntStream.range(0, arr.length()).mapToObj(arr::charAt);
        System.out.println("ordered total: " + countNum(stream));
    }

    private static int countNum(Stream<Character> stream) {
        NumCounter numCounter = stream.reduce(new NumCounter(0, 0, false), NumCounter::accumulate, NumCounter::combine);
        return numCounter.getSum();
    }
}

class NumCounter {
    private int num;
    private int sum;
    private boolean isWholeNum;

    public NumCounter(int num, int sum, boolean isWholeNum) {
        this.num = num;
        this.sum = sum;
        this.isWholeNum = isWholeNum;
    }

    public NumCounter accumulate(Character c) {
        if (Character.isDigit(c)) {
            return isWholeNum ? new NumCounter(Integer.parseInt("" + c), sum + num, false)
                    : new NumCounter(Integer.parseInt("" + num + c), sum, false);
        } else {
            return new NumCounter(0, sum + num, true);
        }
    }

    public NumCounter combine(NumCounter numCounter) {
        return new NumCounter(numCounter.num, this.getSum() + numCounter.getSum(), numCounter.isWholeNum);
    }

    public int getSum() {
        return sum + num;
    }
}
