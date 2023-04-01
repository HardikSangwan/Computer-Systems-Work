import org.junit.Before;
import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;
 
import static org.junit.Assert.*;
 
/**
 * (hopefully) Comprehensive tests for Homework 1
 *
 * @author flynn
 * @version 1.5
 */
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class LinkedListTylersTests {
 
    private SinglyLinkedList<String> list;
 
    public static final int TIMEOUT = 200;
 
    @Before
    public void setUp() {
        list = new SinglyLinkedList<String>();
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_01_addAtIndex_index_exception() {
        list.addAtIndex(-1, "data");
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_02_addAtIndex_index_exception() {
        list.addAtIndex(1, "data");
    }
 
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void test_03_addAtIndex_arg_exception() {
        list.addAtIndex(0, null);
    }
 
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void test_04_addToFront_arg_exception() {
        list.addToFront(null);
    }
 
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void test_05_addToBack_arg_exception() {
        list.addToBack(null);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_06_get_index_exception() {
        list.get(-1);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_07_get_index_exception() {
        list.get(0);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_08_get_index_exception() {
        list.get(1);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_09_removeAtIndex_index_exception() {
        list.removeAtIndex(-1);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_10_removeAtIndex_index_exception() {
        list.removeAtIndex(0);
    }
 
    @Test(timeout = TIMEOUT, expected = IndexOutOfBoundsException.class)
    public void test_11_removeAtIndex_index_exception() {
        list.removeAtIndex(1);
    }
 
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void test_12_removeAtIndex_arg_exception() {
        list.removeAllOccurrences(null);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_13_addToBack() {
        list.addToBack("a");
        assertEquals("a", list.getHead().getData());
        assertEquals("a", list.getTail().getData());
        assertEquals(1, list.size());
        list.addToBack("b");
        assertEquals("a", list.getHead().getData());
        assertEquals("b", list.getTail().getData());
        assertEquals(2, list.size());
        list.addToBack("c");
        compareToArray(new Object[]{"a", "b", "c"}, list);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_14_ToArray() {
        assertArrayEquals(new Object[]{}, list.toArray());
        list.addToBack("a");
        assertArrayEquals(new Object[]{"a"}, list.toArray());
        list.addToBack("b");
        assertArrayEquals(new Object[]{"a", "b"}, list.toArray());
    }
 
    @Test(timeout = TIMEOUT)
    public void test_15_addAtIndex() {
        list.addAtIndex(0, "a");
        compareToArray(new Object[]{"a"}, list);
        list.addAtIndex(1, "b");
        compareToArray(new Object[]{"a", "b"}, list);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_16_addToFront() {
        list.addToFront("b");
        compareToArray(new Object[]{"b"}, list);
        list.addToFront("a");
        compareToArray(new Object[]{"a", "b"}, list);
 
    }
 
    @Test(timeout = TIMEOUT)
    public void test_17_get() {
        list.addToBack("a");
        assertEquals("a", list.get(0));
        list.addToBack("b");
        assertEquals("b", list.get(1));
    }
 
    @Test(timeout = TIMEOUT)
    public void test_18_removeAtIndex() {
        list.addToBack("a");
        assertEquals("a", list.removeAtIndex(0));
        compareToArray(new Object[]{}, list);
        list.addToBack("a");
        list.addToBack("b");
        assertEquals("b", list.removeAtIndex(1));
        compareToArray(new Object[]{"a"}, list);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_19_removeFromFront() {
        list.addToBack("a");
        assertEquals("a", list.removeFromFront());
        compareToArray(new Object[]{}, list);
        list.addToBack("a");
        list.addToBack("b");
        assertEquals("a", list.removeFromFront());
        compareToArray(new Object[]{"b"}, list);
        assertEquals("b", list.removeFromFront());
        assertNull(list.removeFromFront());
    }
 
    @Test(timeout = TIMEOUT)
    public void test_20_removeFromBack() {
        list.addToBack("a");
        assertEquals("a", list.removeFromBack());
        compareToArray(new Object[]{}, list);
        list.addToBack("a");
        list.addToBack("b");
        assertEquals("b", list.removeFromBack());
        compareToArray(new Object[]{"a"}, list);
        assertEquals("a", list.removeFromBack());
        assertNull(list.removeFromBack());
    }
 
    @Test(timeout = TIMEOUT)
    public void test_21_removeAllOccurrences() {
        list.addToBack("a");
        assertFalse(list.removeAllOccurrences("b"));
        assertTrue(list.removeAllOccurrences("a"));
        compareToArray(new Object[]{}, list);
        list.addToBack("y");
        list.addToBack("n");
        assertTrue(list.removeAllOccurrences("n"));
        compareToArray(new Object[]{"y"}, list);
        list.addToBack("n");
        compareToArray(new Object[]{"y", "n"}, list);
        list.addToBack("y");
        list.addToBack("n");
        list.addToBack("y");
        list.addToBack("n");
        assertTrue(list.removeAllOccurrences("n"));
        compareToArray(new Object[]{"y", "y", "y"}, list);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_22_removeAllOccurrences_equality() {
        list.addToBack("a");
        list.addToBack(new String("a"));
        assertFalse(list.removeAllOccurrences("b"));
        assertTrue(list.removeAllOccurrences("a"));
        compareToArray(new Object[]{}, list);
    }
 
    @Test(timeout = TIMEOUT)
    public void test_23_clear() {
        list.addToBack("a");
        list.addToBack("b");
        list.clear();
        compareToArray(new Object[]{}, list);
    }
 
    /**
     * @param arr the array of expected objects against which
     * @param list is tested
     */
    private void compareToArray(Object[] arr, SinglyLinkedList list) {
        int expectedSize = arr.length;
        assertEquals(expectedSize, list.size());
        if (expectedSize == 0) {
            assertTrue(list.isEmpty());
            assertNull(list.getHead());
            assertNull(list.getTail());
        } else {
            assertFalse(list.isEmpty());
            assertNotNull(list.getHead());
            assertNotNull(list.getTail());
            assertArrayEquals(arr, list.toArray());
        }
    }
 
}
