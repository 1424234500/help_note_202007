declare

 v_int int := 0;

 v_id test.id%type;
 v_name test.name%type;
 v_dept test.dept%type;
 
 v_str varchar(20);
 v_str1 v_str%type;
 
 TYPE worker_record_type is record(
      id number(3),
      name varchar2(20) 
 );
 worker_record worker_record_type;
 
 CURSOR test_cursor IS SELECT id, name, dept FROM test;
 TYPE my_table_type IS TABLE OF test_cursor%ROWTYPE INDEX BY BINARY_INTEGER;
 TYPE my_table_type2 IS TABLE OF my_table_type INDEX BY BINARY_INTEGER;
 my_table my_table_type;
 my_table2 my_table_type2;
 
 TYPE my_varray_type IS VARRAY(3) OF NUMBER;
 v_array my_varray_type := my_varray_type(0, 0, 0);
  
 v_test test%ROWTYPE;
 
 
 
 v_emp emp%ROWTYPE;
vv_id emp.id%TYPE;
vv_name emp.name%TYPE;
vv_job emp.job%TYPE;
vv_money emp.money%TYPE;


CURSOR test_cursor2(tid int) IS SELECT id ID_NAME, name NAME_NAME, dept DEPT_NAME from test where id > tid; 
--定义的游标中使用了雇员好参数 游标中的掺乎用同一般的函数参数
test_rec test%ROWTYPE;
--定义了记录行变量用于接收游标返回的每一行记录

 

begin
    


/*
   1. 创建一个带参数的存储过程，其中的输入参数用于接收员工号，默认值
为‘7654’，然后在 emp 表中查询该员工的姓名、部门、薪水信息，通过 dbms_output
包输出。 
指定参数的默认值： 
参数名 [IN | OUT | IN OUT] 数据类型 [{:= | DEFAULT} 表达式] 
例如：a_deptno number := 10 
a. 调用过程，不设置参数值 
b. 调用过程，参数值为‘7788’ 
c. 调用过程，参数值为‘7789’
,
 p_name out scott.emp.name%type,
 p_job out scott.emp.job%type,
 p_money out scott.emp.money%type
   */
create or replace procedure query_emp
(p_id in scott.emp.id%type:=7003)
 
 as 
vv_name scott.emp.name%TYPE;
vv_job scott.emp.job%TYPE;
vv_money scott.emp.money%TYPE;
 
 begin
     select name,job,money into vv_name,vv_job,vv_money 
     from scott.emp 
     where id=p_id;
      dbms_output.put_line('id ' || vv_id || 'name ' || vv_name || 'job ' || vv_job || 'money ' || vv_money   ); 
 end query_emp;  
 
 
  begin     
        query_emp(vv_name, vv_job, vv_money);
        dbms_output.put_line('id ' || vv_id || 'name ' || vv_name || 'job ' || vv_job || 'money ' || vv_money   ); 
  end; 

         
--过程模板
--权限问题 ， sql / cmd
/* 
create or replace procedure query_test
(p_id in scott.test.id%type,
 p_name out scott.test.name%type,
 p_dept out scott.test.dept%type)
 is
 begin
     select name,dept into p_name,p_dept 
     from scott.test 
     where id=p_id;
 end query_test; 
--使用方式
execute query_test(408,:v_name,:v_dept)
 */ 




/* 
  开始一个事务 
  在‘刘程’帐号余额中增加转帐额（5000 元） 
  判断帐号‘李文’中余额是否>=转帐额 
  如果是，则在帐号‘李文’中减转帐额，并提交事务 
  否则，回滚事务 
 */ 
   BEGIN
         update account set balance=balance+v_num where ano=2;                  
   
         select * INTO v_account from account where ano = 1;
        if v_account.balance < v_num then
            update account set balance=balance-v_num where ano=2; 
        else
            update account set balance=balance-v_num where ano=1; 
            commit;
       end if;
        
        EXCEPTION
            WHEN TOO_MANY_ROWS THEN
                DBMS_OUTPUT.PUT_LINE(' EXCEPTION!!!  '); 
            WHEN OTHERS THEN
                NULL;
        END;






 
         BEGIN
             
         WHILE v_int < 6 LOOP
             v_int := v_int + 1;
             DBMS_OUTPUT.PUT_LINE('while: v_int = '|| v_int);
         END LOOP;
         
            FOR i IN 1 .. 4 LOOP 
               DBMS_OUTPUT.PUT_LINE('for: v_i = '|| i);
               
               IF i > 3 THEN
                   EXIT;
               END IF;
               
               
            END LOOP;
         
         END;








         BEGIN
             --游标相关的操作，参数300标识只处理雇员号编号id超过300 的记录, 函数？？？？？？？？？？？？？//
             OPEN test_cursor2(700);
             LOOP
                        FETCH test_cursor2 INTO test_rec;
                        EXIT WHEN test_cursor2%NOTFOUND;            --如果娶不到数据就退出循环 LOOP 退出格式
                    
                        IF test_rec.id < 400 THEN
                           -- UPDATE test set id=test_rec.id*10 where id=test_rec.id;
                            DBMS_OUTPUT.PUT_LINE('=== < 400:'|| test_rec.id);
                        ELSIF test_rec.id < 500 THEN
                            DBMS_OUTPUT.PUT_LINE('=== < 500:'|| test_rec.id);
                        ELSE
                            DBMS_OUTPUT.PUT_LINE('=== > 500:'|| test_rec.id);

                        END IF;
                        
                        CASE test_rec.dept
                             WHEN 10 THEN DBMS_OUTPUT.PUT_LINE('dept:'|| test_rec.dept || ' ' || 'A');
                             WHEN 20 THEN DBMS_OUTPUT.PUT_LINE('dept:'|| test_rec.dept || ' ' || 'b');
                             WHEN 30 THEN DBMS_OUTPUT.PUT_LINE('dept:'|| test_rec.dept || ' ' || 'C');
                             ELSE  DBMS_OUTPUT.PUT_LINE('dept  NO THING !!!!!!!!');
                        END CASE;
                         
             END LOOP;
             CLOSE test_cursor2;
             
             EXCEPTION 
             WHEN OTHERS THEN
                DBMS_OUTPUT.PUT_LINE(' EXCEPTION!!!1111111111111?????????'); 
             
         END;








        BEGIN
         select * INTO v_test from test where id = 10002;
          DBMS_OUTPUT.PUT_LINE('=== id:' ||v_test.id || '  name:' || v_test.name|| '    dept:' || v_test.dept);

         select * INTO v_test from test ;
          DBMS_OUTPUT.PUT_LINE('=== id:' ||v_test.id || '  name:' || v_test.name|| '    dept:' || v_test.dept);
        EXCEPTION
            WHEN TOO_MANY_ROWS THEN
                DBMS_OUTPUT.PUT_LINE(' EXCEPTION!!! too many rows'); 
            WHEN OTHERS THEN
                NULL;
        END;
     



            BEGIN


            FOR i IN v_array.FIRST .. v_array.LAST LOOP
                 v_array(i) := i * 100;
                 DBMS_OUTPUT.PUT_LINE('Index:'|| to_char(i) || 'is:'||to_char(v_array(i)));
            END LOOP;
            v_array(3):= 300;
              DBMS_OUTPUT.PUT_LINE('The array length =  '|| v_array.COUNT);

               
              OPEN test_cursor;
              FETCH test_cursor INTO my_table(1);
              FETCH test_cursor INTO my_table(2);
              FETCH test_cursor INTO my_table(100);
              FETCH test_cursor INTO my_table2(1)(100);
              
              
              CLOSE test_cursor;
              
              DBMS_OUTPUT.PUT_LINE('Output by cursor of table');
              
              DBMS_OUTPUT.PUT_LINE('id:' || my_table(1).id || '  name:' || my_table(1).name|| '    dept:' || my_table(1).dept);
              DBMS_OUTPUT.PUT_LINE('id:' || my_table(2).id || '  name:' || my_table(2).name|| '    dept:' || my_table(2).dept);
              DBMS_OUTPUT.PUT_LINE('id:' || my_table(100).id || '  name:' || my_table(100).name|| '    dept:' || my_table(100).dept);
             
              DBMS_OUTPUT.PUT_LINE('id:' || my_table2(1)(100).id || '  name:' || my_table2(1)(100).name|| '    dept:' || my_table2(1)(100).dept);
              


              DBMS_OUTPUT.PUT_LINE('Output !!');
              
              
              worker_record.id:=10;
              worker_record.name:='Jack';
              DBMS_OUTPUT.PUT_LINE(worker_record.id || ':'||worker_record.name);

             select id,name,dept,name into v_id,v_name,v_dept,v_str
              from test
              where id=10001;
              
              v_str1:=v_str;
              dbms_output.put_line(v_id || 'is a '|| v_str1);
             
             EXCEPTION 
             WHEN OTHERS THEN
                DBMS_OUTPUT.PUT_LINE(' EXCEPTION!!! ????????22222222222'); 
             
              END;
  
  
end;
