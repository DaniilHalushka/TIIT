import unittest
from main import *


class MyTestCase(unittest.TestCase):
    def test_diff_sets(self):
        self.assertEqual(simm_diff_sets([1, 2, 3], [1]), [2, 3])
        self.assertEqual(simm_diff_sets([2, 3, 4], [2]), [3, 4])
        self.assertEqual(simm_diff_sets([1, 2, 3], [2]), [1, 3])
        self.assertEqual(simm_diff_sets([{1, 2, 3}, 1, 4], [1, {1, 2, 3}]), [4])
        self.assertEqual(simm_diff_sets(['{1, 2, 3}', 'a', 1, 'A', '<4, 5>'], ['<4, 5>', '{1, 2, 3}', 4, 'a']), [1, 'A', 4])
        self.assertEqual(simm_diff_sets(['{<4, 5>, <5, 4>}', 4, 'B', 'f'], ['{<4, 5>, <5, 4>}', 4, 'a']), ['B', 'f', 'a'])
        self.assertEqual(simm_diff_sets(['<{1, 2, 3}, 5>', 'F', 5, 4, 'r'], ['<{1, 2, 3}, 5>', 5, 'f']), ['F', 4, 'r', 'f'])
        self.assertEqual(simm_diff_sets([1, 2, 3, 4, 5], ['a', 'b', 'c', 5, 4]), [1, 2, 3, 'a', 'b', 'c'])
        self.assertEqual(simm_diff_sets([1, 2, 3, '{1, 2, 3}', 'b'], [1, 2, 3, '{1, 2, 3}', 'b']), [])
        self.assertEqual(simm_diff_sets([3, 2, 1, '<{}, {}>'], ['<{}, {}>', 4, 1]), [3, 2, 4])

    def test_check(self):
        self.assertEqual(check('{2,1,3}'), ['1', '2', '3'])
        self.assertEqual(check('{1,7,5,4}'), ['1', '4', '5', '7'])
        self.assertEqual(check('{1,f,5,r,A}'), ['1', '5', 'A', 'f', 'r'])
        self.assertEqual(check('{1,r,f,B}'), ['1', 'B', 'f', 'r'])
        self.assertEqual(check('{1,5,3,4,f,B,A}'), ['1', '3', '4', '5', 'A', 'B', 'f'])
        self.assertEqual(check('{1,0,5,3,4,B,a,R}'), ['0', '1', '3', '4', '5', 'B', 'R', 'a'])
        self.assertEqual(check('{5,3,4,1,A,R,f,a}'), ['1', '3', '4', '5', 'A', 'R', 'a', 'f'])
        self.assertEqual(check('{1,5,f,s,a,r,g,h}'), ['1', '5', 'a', 'f', 'g', 'h', 'r', 's'])
        self.assertEqual(check('{q,w,e,r,t,y,u,i,o}'), ['e', 'i', 'o', 'q', 'r', 't', 'u', 'w', 'y'])
        self.assertEqual(check('{p,l,o,k,i,j,u,h,g,y,f,t}'), ['f', 'g', 'h', 'i', 'j', 'k', 'l', 'o', 'p', 't', 'u', 'y'])

    def test_correct_input(self):
        self.assertEqual(correct_input('.'), False)
        self.assertEqual(correct_input('{1,2,3}'), True)
        self.assertEqual(correct_input('{{},1,2,3,<4,5>}'), True)
        self.assertEqual(correct_input('{,m.f.d.,s}'), False)
        self.assertEqual(correct_input('{a,A,b,C,v,R,7,5}'), True)
        self.assertEqual(correct_input('{1,2,3,4,5}.'), False)
        self.assertEqual(correct_input('.{a,F,A,d,D}'), False)
        self.assertEqual(correct_input('{1,2,3,4,5,yguuv,iugyug}-'), False)
        self.assertEqual(correct_input('true'), True)
        self.assertEqual(correct_input('{true}'), True)


if __name__ == '__main__':
    unittest.main()
