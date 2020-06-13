package you.chen.ctest;

public class HashMap<K, V> {
    /**
     * 散列值
     */
    private Entry<K, V>[] table;

    transient int size;

    /**
     * 阀值, 2的幂次
     */
    int threshold;

    /**
     * 扩容因子 , 也有一些技巧
     */
    final float loadFactor = 0.75f;

    public HashMap() {
        this(7);
    }

    public HashMap(int threshold) {
        threshold |= threshold >> 1;
        threshold |= threshold >> 2;
        threshold |= threshold >> 4;
        threshold |= threshold >> 8;
        threshold |= threshold >> 16;
        this.threshold = threshold + 1;
        table = new Entry[threshold];
    }


    public int size() {
        return table.length;
    }


    public V put(K key, V value) {
        if (key == null) return null;
        int hash = hash(key);
        int index = getIndex(hash, threshold);
        for (Entry<K, V> entry = table[index]; entry != null; entry = entry.next) {
            if (entry.hash == hash && (entry.key == key || key.equals(entry.key))) {
                V oldV = entry.value;
                entry.value = value;
                return oldV;
            }
        }
        newEntry(hash, key, value, index);
        return null;
    }

    private void newEntry(int hash, K key, V value, int index) {



        // hash_shift 16  value() >> 16
        // 判断要不要扩容  jni 源码记住  mask_bits(value() >> hash_shift, hash_mask)
        // 1. hash 值相等两个对象不一定相等 （两个对象不相等 hash 值有可能相等）
        // 2. hash 值不相等的两个对象，这两个对象肯定不相等
        if(size >= threshold && table[index] != null){
            //resize(size << 1);
            // 重新计算 index
            index = getIndex(hash,table.length);
        }
        // 添加
        //createEntry(hash,key,value,index);

        size++;
    }

    private static <E> int hash(E key) {
        int h = 0;
        return (key == null) ? 0 : (h = key.hashCode() ^ (h >>> 16));
    }

    /**
     * 通过hash值计算index
     * @param hash
     * @return
     */
    private static int getIndex(int hash, int length) {
        return hash & length - 1;
    }


    public static class Entry<K, V> {

        int hash;

        K key;

        V value;

        Entry<K, V> next;

        Entry(int hash, K key, V value, Entry<K, V> next) {
            this.hash = hash;
            this.key = key;
            this.value = value;
            this.next = next;
        }
    }


}
