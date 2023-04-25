SELECT COUNT(ID) AS Amount, CAST(JULIANDAY(Completion) - JULIANDAY(Acceptance) AS INTEGER) as Days
FROM [Order]
GROUP BY (JULIANDAY(Completion) - JULIANDAY(Acceptance))
HAVING Completion != 'NULL';