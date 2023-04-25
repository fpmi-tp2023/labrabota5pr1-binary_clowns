SELECT Flower.Kind, SUM(FlowersAmount * CompAmount) as TotalAmount
FROM FlowerComp
INNER JOIN (
	SELECT OrderComp.CompositionID, OrderComp.OrderID, SUM(OrderComp.CompositionAmount) as CompAmount
	FROM (
		SELECT [Order].ID FROM [Order] 
		WHERE [Order].Completion != 'NULL' AND [Order].Completion > '2023-01-01'
			AND [Order].Completion < '2023-04-01'
	) A
	INNER JOIN OrderComp ON OrderComp.OrderID == A.ID
	GROUP BY OrderComp.CompositionID
) F ON FlowerComp.CompositionID == F.CompositionID
INNER JOIN Flower ON Flower.ID = FlowerComp.FlowerID
GROUP BY Flower.Kind