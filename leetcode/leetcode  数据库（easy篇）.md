176.第二高的薪水

```
select (
select DISTINCT Salary #去重
from Employee
ORDER BY Salary DESC #降序排列
limit 1 offset 1 #从第一条数据读取（offset 1 ，但不包括第一条），往后读取一条数据（limit1 ），即第二条；
) as SecondHighestSalary;
```

\596. 超过5名学生的课

```
SELECT class from courses group by class having count(DISTINCT student) >= 5;
```

\197. 上升的温度

```
select Id
from Weather a, Weather b
where a.Temperature > b.Temperature
and DATEDIFF(a.RecordDate, b.RecordDate) = 1
```

\196. 删除重复的电子邮箱

```
DELETE p2 FROM Person as p1, Person as p2
wHERE p1.Email = p2.Email AND p2.Id > p1.Id
```

\181. 超过经理收入的员工

```
SELECT Worker.Name AS Employee
FROM Employee AS Worker, Employee AS Manager
WHERE Worker.ManagerId = Manager.Id AND Worker.Salary > Manager.Salary
```


\183. 从不订购的客户

```
select Name as Customers
from Customers
where Id not in(
select C.Id
from Customers as C, Orders as O
where C.Id = O.CustomerId)
```

\175. 组合两个表

```
SELECT FirstName, LastName, City, State
FROM Person LEFT JOIN Address
ON Person.PersonId = Address.PersonId
```

\595. 大的国家

```
select name,population,area from  World where (area >3000000) or (population>25000000)
```

\182. 查找重复的电子邮箱

```
select distinct Email from Person  group by Email having count(Email) > 1;
```

\627. 交换工资

```
UPDATE salary SET sex = (CASE WHEN sex = 'm' THEN 'f' ELSE 'm' END)
```

\620. 有趣的电影

```
select * from cinema where description<>'boring' and MOD(id,2)=1 ORDER BY rating desc
```

