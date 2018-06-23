package test

fun add(a: Int, b: Int, vararg n: Int): Int {
    var sum = a + b
    for(i in n)
    {
        sum += i
    }
    return sum
}

fun max(a: Int, b: Int) = if (a <= b) b else a

val x: Int = 1
val arrayInt = intArrayOf(6, 7, 8, 9, 10)

val isOdd = when {
    (x and 1) == 1 -> true
    else -> false
}

fun testFor(array: IntArray)
{
    for(item in array)
    {
        println("$item")
    }
    for(i in array.indices)
    {
        println("array[$i] is ${array[i]}")
    }
    for((index, value) in array.withIndex())
    {
        println("array[$index] is $value")
    }

    for(i in 1..5) println(i)
    for(i in 5 downTo 1) println(i)
    for(i in 10 downTo 1 step 3) println(i)
    for(i in 1..5 step 2) println(i)
}

fun testLoop()
{
    loop@ for(i in 1..10)
    {
        for(j in 1..10)
        {
            println("i = $i j = $j")
            if(i > 5) break@loop
        }
    }

    println()

    val ints = intArrayOf(1, 2, 3)
    ints.forEach {
        if (it == 2) return
        println(it)
    }
}

fun main(args: Array<String>)
{

    //println(isOdd);
    //println(max(10, 20));
    //println(add(10, 20, 30, 40, 50));
    //testFor(arrayInt)
    testLoop()
}