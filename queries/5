SELECT FlowerComp.CompositionID, Composition.Name, F.Amount,
		SUM(FlowersAmount*Flower.Price) as CompPrice,
		SUM(FlowersAmount*Flower.Price)*F.Amount as TotalPrice 
FROM FlowerComp
INNER JOIN (
	SELECT CompositionID, SUM(CompositionAmount) as Amount
	FROM OrderComp
	GROUP BY CompositionID
) F ON FlowerComp.CompositionID == F.CompositionID
INNER JOIN Flower ON Flower.ID = FlowerComp.FlowerID
INNER JOIN Composition ON Composition.ID = F.CompositionID
GROUP BY FlowerComp.CompositionID