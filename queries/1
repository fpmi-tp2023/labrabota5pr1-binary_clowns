SELECT SUM(K.TotalPrice) as EarnPerPeriod
FROM
(	SELECT FlowerComp.CompositionID, F.TotalAmount,
		SUM(FlowersAmount*Flower.Price) as CompPrice,
		SUM(FlowersAmount*Flower.Price)*F.TotalAmount as TotalPrice 
	FROM FlowerComp
	INNER JOIN (
		SELECT OrderComp.CompositionID, OrderComp.OrderID, SUM(OrderComp.CompositionAmount) as TotalAmount
		FROM (
			SELECT [Order].ID FROM [Order] 
			WHERE [Order].Completion != 'NULL' AND [Order].Completion > '2023-01-01'
				AND [Order].Completion < '2023-04-01' AND [Order].CustomerID = 1
		) A
		INNER JOIN OrderComp ON OrderComp.OrderID == A.ID
		GROUP BY OrderComp.CompositionID
	) F ON FlowerComp.CompositionID == F.CompositionID
	INNER JOIN Flower ON Flower.ID = FlowerComp.FlowerID
	GROUP BY FlowerComp.CompositionID
) K