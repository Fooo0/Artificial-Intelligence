# -*- coding: utf-8 -*-
"""
Created on Sun Dec 20 13:11:37 2015

@author: 宋佳飞
"""

class Node(object):
    def __init__(self, father, state, f, g):
        self.father = father
        self.state = state
        self.f = f    # 总估价
        self.g = g    # 根到该节点的实际代价

def Calculate_h(state):    # 计算至目标节点的估价
    h = 0
    aim_w=0    # 计数 aim_w号（0开始）白色将牌前的黑色数
    while aim_w < 3:    # 3白
        count_w = aim_w
        for item in state:
            if item == 'B':
                h += 1
            elif item == 'W':
                if count_w == 0:
                    break
                else:
                    count_w -= 1
        aim_w += 1
    return h

def Change(node, index, direction, terminal):    # 跳或者移动到相邻，terminal 可为1（移动），2（跳1），3（跳2）
    if direction == 0:    # 左
        if index - terminal < 0 or node.state[index - terminal] != 'E':
            return -1
        else:
            son_state = node.state[:]
            son_state[index - terminal], son_state[index] = son_state[index], son_state[index - terminal]
            h = Calculate_h(son_state)
            son_node=Node(node, son_state, h + node.g + terminal, node.g + terminal)
            return son_node
    elif direction == 1:    # 右
        if index + terminal > 6 or node.state[index + terminal] != 'E':
            return -1
        else:
            son_state = node.state[:]
            son_state[index], son_state[index + terminal] = son_state[index + terminal], son_state[index]
            h = Calculate_h(son_state)
            son_node=Node(node, son_state, h + node.g + terminal, node.g + terminal)
            return son_node
            
def Select_min(open_list):
    if open_list:
        index_min = 0
        index = 1
        while index < len(open_list):
            if open_list[index].f < open_list[index_min].f:
                index_min = index
            index += 1
        return  index_min
    return -1

def Reach_aim(node):
    if Calculate_h(node.state) == 0:
        return True
    return False

def Extend_father(node):
    all_sons = []
    index = 0
    while index < len(node.state):
        if node.state[index] == 'E':
            break
        index += 1
    for terminal in [1,2,3]:
        if index - terminal >= 0:
            son = Change(node, index - terminal, 1, terminal)
            all_sons.append(son)
        if index + terminal <= 6:
            son = Change(node, index + terminal, 0, terminal)
            all_sons.append(son)
    return all_sons

def Node_in_open(open_list, node):
    for item in open_list:
        if item.state == node.state:
            return item
    return None

def Node_in_close(close_list, node):
    for item in close_list:
        if item.state == node.state:
            return item
    return None

def Print_path(node):
    path = []
    while node:
        path.append(node.state)
        node = node.father
    path = path[::-1]
    print path[0],
    for p in path[1:]:
        print '->',p,
            
open_list = []
close_list = []
start = Node(None,['B','B','B','W','W','W','E'],0,0)
start.f = Calculate_h(start.state)
open_list.append(start)
while open_list:
    father_node = open_list.pop(Select_min(open_list))
    if Reach_aim(father_node):
        break
    else:
        all_sons = Extend_father(father_node)
        for son in all_sons:
            repeat = Node_in_open(open_list, son)
            if repeat:
                if repeat.f > son.f:
                    repeat.father, repeat.f, repeat.g = father_node, son.f, son.g
                    continue
            repeat =  Node_in_close(open_list, son)
            if repeat:
                continue
            else:
                open_list.append(son)
    close_list.append(father_node)

Print_path(father_node)