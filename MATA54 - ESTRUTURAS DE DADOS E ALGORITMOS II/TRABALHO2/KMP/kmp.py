from typing import Generator, Optional, Sequence

class Seq:
    def __init__(self, sequence: Sequence):
        self.__sequence = sequence
        self.__interactions = 0

    def __getitem__(self, index):
        self.__interactions += 1
        return self.__sequence[index]

    def get_interactions(self):
        return self.__interactions
        


class KMPSearch(object):
    """
    Algorithm KMP for matching pattern in sequences.
    """
    def __init__(self, pattern: Sequence, pattern_length: Optional[int] = None):
        if pattern_length is None:
            pattern_length = len(pattern)

        # Instantiate the parameters.
        self.__pattern = pattern
        self.__pattern_iter = 0
        self.__pattern_length = pattern_length

        self.__lps: list = [0]  # List to save the LPS (longest prefix which is also a suffix).

        # Process the pattern.
        for index in range(1, self.__pattern_length):
            j = self.__lps[index - 1]

            self.__pattern_iter += 2 if j > 0 else 1

            while j > 0 and pattern[j] != pattern[index]:
                j = self.__lps[j - 1]
                if j > 0: self.__pattern_iter += 1

            self.__lps.append(j + 1 if pattern[j] == pattern[index] else j)

    def search(self, sequence: Sequence, length: Optional[int] = None) -> Generator[tuple[int, int], None, None]:
        """
        Return all the matching position of pattern.
        """
        if length is None:
            length = len(sequence)

        sequence = Seq(sequence)

        offset = 0
        inter = 0

        for index in range(length):
            
            while offset > 0 and sequence[index] != self.__pattern[offset]:
                offset = self.__lps[offset - 1]

            if sequence[index] == self.__pattern[offset]:
                offset += 1

            if offset == self.__pattern_length:
                yield index - (offset - 1), sequence.get_interactions() + self.__pattern_iter
                offset = self.__lps[offset - 1]
