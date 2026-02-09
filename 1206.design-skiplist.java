#
# @lc app=leetcode id=1206 lang=java
#
# [1206] Design Skiplist
#
# @lc code=start
import java.util.Random;

class Skiplist {
    static final int MAX_LEVEL = 16;
    static final double P = 0.5;
    final Node head = new Node(-1, MAX_LEVEL);
    int level = 1;
    Random rand = new Random();

    static class Node {
        int val;
        Node[] forward;
        Node(int val, int level) {
            this.val = val;
            this.forward = new Node[level];
        }
    }

    public Skiplist() {}

    private int randomLevel() {
        int lvl = 1;
        while (lvl < MAX_LEVEL && rand.nextDouble() < P) {
            lvl++;
        }
        return lvl;
    }

    public boolean search(int target) {
        Node curr = head;
        for (int i = level - 1; i >= 0; --i) {
            while (curr.forward[i] != null && curr.forward[i].val < target) {
                curr = curr.forward[i];
            }
        }
        curr = curr.forward[0];
        return curr != null && curr.val == target;
    }

    public void add(int num) {
        Node[] update = new Node[MAX_LEVEL];
        Node curr = head;
        for (int i = level - 1; i >= 0; --i) {
            while (curr.forward[i] != null && curr.forward[i].val < num) {
                curr = curr.forward[i];
            }
            update[i] = curr;
        }
        int lvl = randomLevel();
        if (lvl > level) {
            for (int i = level; i < lvl; ++i) {
                update[i] = head;
            }
            level = lvl;
        }
        Node newNode = new Node(num, lvl);
        for (int i = 0; i < lvl; ++i) {
            newNode.forward[i] = update[i].forward[i];
            update[i].forward[i] = newNode;
        }
    }

    public boolean erase(int num) {
        Node[] update = new Node[MAX_LEVEL];
        Node curr = head;
        for (int i = level - 1; i >= 0; --i) {
            while (curr.forward[i] != null && curr.forward[i].val < num) {
                curr = curr.forward[i];
            }
            update[i] = curr;
        }
        curr = curr.forward[0];
        if (curr == null || curr.val != num) return false;
        for (int i = 0; i < level; ++i) {
            if (update[i].forward[i] != curr) break;
            update[i].forward[i] = curr.forward[i];
        }
        while (level > 1 && head.forward[level - 1] == null) {
            level--;
        }
        return true;
    }
}

/**
* Your Skiplist object will be instantiated and called as such:
* Skiplist obj = new Skiplist();
* boolean param_1 = obj.search(target);
* obj.add(num);
* boolean param_3 = obj.erase(num);
*/
# @lc code=end