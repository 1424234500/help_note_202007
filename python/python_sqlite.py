#!/usr/bin/python
#-*- coding:utf-8 -*-   
import sqlite3
import os 
import sys
sys.path.append("../")
import tool

#
# 连接数据库帮助类
# eg:
#   db = database()
#   count,listRes = db.executeQueryPage("select * from student where id=? and name like ? ", 2, 10, "id01", "%name%")
#   listRes = db.executeQuery("select * from student where id=? and name like ? ", "id01", "%name%")
#   db.execute("delete from student where id=? ", "id01")
#   count = db.getCount("select * from student ")
#   db.close()
#
class Database :
    dbfile = "sqlite.db"
    memory = ":memory:"
    conn = None
    showsql = False

    def __init__(self, dbfile=''):
        if(dbfile == ''):
            dbfile = self.dbfile
        self.dbfile = dbfile
        self.conn = self.getConn()
    #输出工具
    def out(self, outStr, *args):
        if(self.showsql):
            for var in args:
                if(var):
                    outStr = outStr + ", " + str(var)
            print("db. " + outStr)
        return 
    #获取连接
    def getConn(self):
        if(self.conn is None):
            conn = sqlite3.connect(self.dbfile, check_same_thread=False )
            if(conn is None):
                conn = sqlite3.connect(self.memory, check_same_thread=False )
            if(conn is None):
                self.out("dbfile : " + self.dbfile + " is not found && the memory connect error ! ")
            else:
                conn.row_factory = self.dict_factory #字典解决方案
                self.conn = conn
                conn.text_factory = str     # sqlite3.ProgrammingError: You must not use 8-bit bytestrings unless
            # self.out("db init conn ok ! ")
        else:
            conn = self.conn

        return conn
    #字典解决方案
    def dict_factory(self, cursor, row): 
        d = {} 
        for idx, col in enumerate(cursor.description): 
            d[col[0]] = row[idx] 
        return d
    #关闭连接
    def close(self, conn=None):
        res = 2
        if(not conn is None):
            conn.close()
            conn = None
            res = res - 1
        if(not self.conn is None):
            self.conn.close()
            self.conn = None
            res = res - 1
        self.out("db close res : " + str(res))
        return res
    
    #加工参数tuple or list 获取合理参数list
    #把动态参数集合tuple转为list 并把单独的传递动态参数list从tuple中取出作为参数
    def turnArray(self, args):
        #args (1, 2, 3) 直接调用型 exe("select x x", 1, 2, 3)
        #return [1, 2, 3] <- list(args)
        #args ([1, 2, 3], ) list传入型 exe("select x x",[ 1, 2, 3]) len(args)=1 && type(args[0])=list
        #return [1, 2, 3]
        if(args and len(args) == 1 and (type(args[0]) is list) ):
            res = args[0]
        else:
            res = list(args)
        return res
    #分页查询 查询page页 每页num条 返回 分页前总条数 和 当前页的数据列表 count,listR = db.executeQueryPage("select x x",1,10,(args))
    def executeQueryPage(self, sql, page, num, *args):
        args = self.turnArray(args)
        count = self.getCount(sql, args)

        offset = (int(num) * (int(page) - 1) )
        pageSql = "select * from ( " + sql + " ) limit " + str(num) + " offset " + str(offset) + " "
        listRes = self.executeQuery(pageSql, args)
        return (count, listRes)  

    def executeQueryOffset(self, sql, offset, num, *args):
        args = self.turnArray(args)
        # count = self.getCount(sql, args)

        pageSql = "select * from ( " + sql + " ) limit " + str(num) + " offset " + str(offset) + " "
        listRes = self.executeQuery(pageSql, args)
        return listRes


    #查询列表array[map] eg: [{'id': u'id02', 'birth': u'birth01', 'name': u'name02'}, {'id': u'id03', 'birth': u'birth01', 'name': u'name03'}]
    def executeQuery(self, sql, *args):
        args = self.turnArray(args)
        # self.out(sql, args) 

        conn = self.getConn()
        cursor = conn.cursor()
        res = cursor.execute(sql, args).fetchall()

        if(res is not None):
            for item in res:
                for key in item:
                    item[key] = tool.encode(item[key])
        else:
            res = []
        # self.close()
        return res   
    def executeQueryOne(self, sql, *args):
        args = self.turnArray(args)
        listMap = self.executeQuery(sql, args)
        if(listMap is not None and len(listMap) > 0):
            return listMap[0]
        else:
            return {}
    def execSQL(self, sql, *args):
        args = self.turnArray(args)
        return self.execute(sql, args)
    #执行sql或者查询列表 并提交
    def execute(self, sql, *args):
        args = self.turnArray(args)
        # self.out(sql, args) 

        conn = self.getConn()
        cursor = conn.cursor()
        #sql占位符 填充args 可以是tuple(1, 2)(动态参数数组) 也可以是list[1, 2] list(tuple) tuple(list)
        res = cursor.execute(sql, args).fetchall()
        conn.commit()
        # self.close()
        return res   
    #查询列名列表array[str]  eg: ['id', 'name', 'birth']
    def getColumnNames(self, sql, *args):
        args = self.turnArray(args)
        # self.out(sql, args) 

        conn = self.getConn()
        if(not conn is None):
            cursor = conn.cursor()
            cursor.execute(sql, args)
            res = [tuple[0] for tuple in cursor.description]
        self.close()
        return res   
    #查询结果为单str eg: 'xxxx'
    def getString(self, sql, *args):
        args = self.turnArray(args)
        self.out(sql, args) 

        conn = self.getConn()
        cursor = conn.cursor()
        listRes = cursor.execute(sql, args).fetchall()
        columnNames = [tuple[0] for tuple in cursor.description]
        #print(columnNames)
        res = ""
        if(listRes and len(listRes) >= 1):
            res = listRes[0][columnNames[0]]
        return res      
    #查询记录数量 自动附加count(*) eg: 3
    def getCount(self, sql, *args):
        args = self.turnArray(args)
        sql = "select count(*) cc from ( " + sql + " ) "
        resString = self.getString(sql, args)   
        res = 0     
        if(resString):
            res = int(resString)
        return res


####################################测试
def main():
    db = Database()
    db.execute(
        ''' 
        create table if not exists student(
            id      text primary key,
            name    text not null,
            birth   text 
        )
        ''' 
    )
    for i in range(10):
        db.execute("insert into student values('id1" + str(i) + "', 'name1" + str(i) + "', 'birth1" + str(i) + "')")
    db.execute("insert into student values('id01', 'name01', 'birth01')")
    db.execute("insert into student values('id02', 'name02', 'birth01')")
    db.execute("insert into student values('id03', 'name03', 'birth01')")
  
    print(db.getColumnNames("select * from student"))
    print(db.getCount("select * from student "  ))
    print(db.getString("select name from student where id = ? ", "id02"  ))
    
    print(db.executeQuery("select * from student where 1=? and 2=? ", 1, 2 ))
    print(db.executeQueryPage("select * from student where id like ? ", 1, 5, "id0%"))
    db.execute("update  student set name='nameupdate' where id = ? ", "id02")
    db.execute("delete from student where id = ? or 1=1 ", "id01")
    
    db.close()

if __name__ == '__main__':
    main()

 
