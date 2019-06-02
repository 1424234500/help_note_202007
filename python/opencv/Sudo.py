#!/usr/bin/python
#-*- coding:utf-8 -*-  

class Sudo:
    """ a tool to prase sudo the game """ 

    ## 数独求解算法，回溯法。来源见下面链接，有细微改动。
    ## http://stackoverflow.com/questions/1697334/algorithm-for-solving-sudoku
    def findNextCellToFill(self, grid, i, j):
        for x in range(i,9):
            for y in range(j,9):
                if grid[x][y] == 0:
                    return x,y
        for x in range(0,9):
            for y in range(0,9):
                if grid[x][y] == 0:
                    return x,y
        return -1,-1

    def isValid(self, grid, i, j, e):
        rowOk = all([e != grid[i][x] for x in range(9)])
        if rowOk:
            columnOk = all([e != grid[x][j] for x in range(9)])
            if columnOk:
                # finding the top left x,y co-ordinates of the section containing the i,j cell
                secTopX, secTopY = 3 *int(i/3), 3 *int(j/3)
                for x in range(secTopX, secTopX+3):
                    for y in range(secTopY, secTopY+3):
                        if grid[x][y] == e:
                            return False
                    return True
        return False

    def solveSudoku(self, grid, i=0, j=0):
        i,j = self.findNextCellToFill(grid, i, j)
        if i == -1:
            return True
        for e in range(1,10):
            if self.isValid(grid,i,j,e):
                grid[i][j] = e
                if self.solveSudoku(grid, i, j):
                    return True
                # Undo the current cell for backtracking
                grid[i][j] = 0
        return False

