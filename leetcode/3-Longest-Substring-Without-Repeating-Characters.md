Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

```python
class Solution:
    # 方法1
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = 0
        current_len = 0
        viewed = []
        k = 0
        i = 0
        times = 0

        while k < len(s):
            if s[k] in viewed:
                if current_len > max_len:
                    max_len = current_len
                for i in range(k-1, -1, -1):
                    if s[i] == s[k] and i != k:
                        k = i
                        break
                viewed = []
                current_len = 0
            else:
                viewed.append(s[k])
                current_len += 1
            k += 1
            times += 1
        if current_len > max_len:
            max_len = current_len
        return max_len, times

    # 方法2 是方法1的精简
    # 主要思想是避免重复遍历没问题的substring
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len, start, viewed = 0, 0, {}

        for k, c in enumerate(s):
            if c in viewed and start <= viewed[c]:
                start = viewed[c] + 1
            else:
                max_len = max(max_len, k - start + 1)

            viewed[c] = k

        return max_len
```
