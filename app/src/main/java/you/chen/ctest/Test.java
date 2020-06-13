package you.chen.ctest;

public class Test {

    public static void main(String[] args) {
        System.out.println(aa(16));
    }

    public static int aa(int threshold) {
        threshold |= threshold >> 1;
        threshold |= threshold >> 2;
        threshold |= threshold >> 4;
        threshold |= threshold >> 8;
        threshold |= threshold >> 16;
        threshold++;
        return threshold;
    }


}
