package 

import java.util.HashMap;
import java.util.Map;

/**
 * stolen from Tushar Roy
 *
 */

public class Trie {

    private class TrieNode {
        Map<Character, TrieNode> children;
        boolean isCompleteWord;     
        
        public TrieNode() {
            children = new HashMap<>();
            isCompleteWord = false;
        }
    }
    private final TrieNode root;
    public Trie() {
        root = new TrieNode();
    }

    /**
     * Insertion (iterative)
     */
    public void insert(String word) {
        TrieNode current = root;
        for (int i = 0; i < word.length(); i++) {
            char character = word.charAt(i); /* find character at i in string */
            TrieNode node = current.children.get(character);
            if (node == null) {
                node = new TrieNode();
                current.children.put(character, node);
            }
            current = node;
        }
        current.isCompleteWord = true;
    }

    /**
     * Insertion (recursive)
     */
    public void insertRecursive(String word) {
        insertRecursive(root, word, 0);
    }

    private void insertRecursive(TrieNode current, String word, int index) {
        if (index == word.length()) {
            current.isCompleteWord = true;
            return;
        }
        char character = word.charAt(index);
        TrieNode node = current.children.get(character);

        // if node does not exist in map, create one and put into map
        if (node == null) {
            node = new TrieNode();
            current.children.put(character, node);
        }
        insertRecursive(node, word, index + 1);
    }
}
