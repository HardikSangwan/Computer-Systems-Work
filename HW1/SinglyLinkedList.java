/**
 * Your implementation of a SinglyLinkedList
 *
 * @author Nikhil Dhanda
 * @version 1.0
 */
public class SinglyLinkedList<T> implements LinkedListInterface<T> {

    // Do not add new instance variables.
    private LinkedListNode<T> head;
    private LinkedListNode<T> tail;
    private int size;

    @Override
    public void addAtIndex(int index, T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data for the node "  
                + "is null");
        }
        LinkedListNode<T> newNode = new LinkedListNode<T>(data);
        if (index > size || index < 0) {
            throw new java.lang.IndexOutOfBoundsException("Cannot add at this"  
                + " index since index is either out of bounds or is negative");
        } else if (size == 0) {
            head = newNode;
            tail = newNode;
            size = size + 1;
        } else if (index == 0) {
            head = new LinkedListNode<T>(data, head);
            size = size + 1;
        } else if (index == size) {
            LinkedListNode<T> current = tail;
            current.setNext(newNode);
            tail = newNode;
            size = size + 1;
        } else {
            int counter = 1;
            LinkedListNode<T> current = head;
            while (counter < index) {
                current = current.getNext();
                counter++;
            }
            LinkedListNode<T> nextNode = current.getNext();
            current.setNext(newNode);
            newNode.setNext(nextNode);
            size = size + 1;
        }
        
    }

    @Override
    public T get(int index) {
        if (index >= size || index < 0) {
            throw new java.lang.IndexOutOfBoundsException("Cannot add at this"  
               + " index since index is either out of bounds or is negative");
        }
        if (index == 0) {
            return head.getData();
        } else if (index == (size - 1)) {
            return tail.getData();
        } else {
            int counter = 0;
            LinkedListNode<T> current = head;
            while (counter < index) {
                current = current.getNext();
                counter++;
            }
            return current.getData();
        }

    }

    @Override
    public T removeAtIndex(int index) {
        if (index >= size || index < 0) {
            throw new java.lang.IndexOutOfBoundsException("Cannot add at this"  
               + " index since index is either out of bounds or is negative");
        } else if (index == 0) {
            LinkedListNode<T> nodeToBeRemoved = head;
            head = nodeToBeRemoved.getNext();
            nodeToBeRemoved.setNext(null);
            size = size - 1;
            if (size == 0) {
                tail = null;
            }
            return nodeToBeRemoved.getData();
        }  else {
            int counter = 1;
            LinkedListNode<T> current = head;
            while (counter < index) {
                current = current.getNext();
                counter++;
            }
            LinkedListNode<T> nodeToBeRemoved = current.getNext();
            LinkedListNode<T> nextNode = nodeToBeRemoved.getNext();
            nodeToBeRemoved.setNext(null);
            current.setNext(nextNode);
            if (nextNode == null) {
                tail = current;
            }
            size = size - 1;
            return nodeToBeRemoved.getData();
        }
        

    }

    @Override
    public void addToFront(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data for the node "  
            + "is null");
        }
        if (size == 0) {
            LinkedListNode<T> newNode = new LinkedListNode<T>(data);
            head = newNode;
            tail = newNode;
            size = size + 1;

        } else {
            head = new LinkedListNode<T>(data, head);
            size = size + 1;
        }
    }

    @Override
    public void addToBack(T data) {
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data for the node "  
            + "is null");
        }        
        if (size == 0) {
            LinkedListNode<T> newNode = new LinkedListNode<T>(data);
            head = newNode;
            tail = newNode;
            size = size + 1;

        } else {
            LinkedListNode<T> newNode = new LinkedListNode<T>(data);
            LinkedListNode<T> current = tail;
            current.setNext(newNode);
            tail = newNode;
            size = size + 1;

        }
        
    }

    @Override
    public T removeFromFront() {
        if (size == 0) {
            return null;
        } else {
            LinkedListNode<T> nodeToBeRemoved = head;
            head = head.getNext();
            nodeToBeRemoved.setNext(null);
            size = size - 1;
            if (size == 0) {
                tail = null;
            }
            return nodeToBeRemoved.getData();
        }
        
    }

    @Override
    public T removeFromBack() {
        if (size == 0) {
            return null;
        } else if (size == 1) {
            LinkedListNode<T> nodeToBeRemoved = head;
            head = null;
            tail = null;
            size = size - 1;
            return nodeToBeRemoved.getData();
        } else {
            int counter = 1;
            LinkedListNode<T> current = head;
            while (counter < (size - 1)) {
                current.getNext();
                counter++;
            }
            LinkedListNode<T> nodeToBeRemoved = current.getNext();
            current.setNext(null);
            tail = current;
            size = size - 1;
            return nodeToBeRemoved.getData();

        }
        
    }

    @Override
    public boolean removeAllOccurrences(T data) {
        boolean result = false;
        if (data == null) {
            throw new java.lang.IllegalArgumentException("Data for the node "  
            + "is null");
        } else {
            LinkedListNode<T> current = head;
            if (head == null) {
                return false;
            }
            if (size == 1) {
                if (head.getData().equals(data)) {
                    head = null;
                    tail = null;
                    size = size - 1;
                    return true;
                }
            } else {
                while (current.getNext() != null) {
                    if (head.getData().equals(data)) {
                        head = head.getNext();
                        size = size - 1;
                        if (head == null) {
                            tail = null;
                            return result;
                        }
                        result = true;
                    } else if (current.getNext().getData().equals(data)) {
                        LinkedListNode<T> nodeToBeRemoved = current.getNext();
                        LinkedListNode<T> nextNode = nodeToBeRemoved.getNext();
                        current.setNext(nextNode);
                        nodeToBeRemoved.setNext(null);
                        if (nextNode == null) {
                            tail = current;
                        }
                        size = size - 1;
                        result = true;
                    } else {
                        current = current.getNext();
                    }
                }

            } 
        }
        return result;
    }

    @Override
    public Object[] toArray() {
        Object[] array = new Object[size];
        LinkedListNode<T> current = head;
        int i = 0;
        while (i < (array.length)) {
            array[i] = current.getData();
            current = current.getNext();
            i++;
        }
        return array;
    }

    @Override
    public boolean isEmpty() {
        return (head == null);

    }

    @Override
    public int size() {
        return size;

    }

    @Override
    public void clear() {
        head = null;
        tail = null;
        size = 0;
    }

    @Override
    public LinkedListNode<T> getHead() {
        // DO NOT MODIFY!
        return head;
    }

    @Override
    public LinkedListNode<T> getTail() {
        // DO NOT MODIFY!
        return tail;
    }
}
