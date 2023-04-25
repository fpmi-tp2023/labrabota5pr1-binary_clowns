SELECT FlowerID, Flower.Name, FlowersAmount, Flower.Price, CompositionID, A.Name as CompositionName
FROM (
	SELECT * FROM FlowerComp 
	INNER JOIN Composition ON Composition.ID == FlowerComp.CompositionID) A
INNER JOIN Flower ON Flower.ID == A.FlowerID AND A.CompositionID == (
	SELECT OrderComp.CompositionID
	FROM OrderComp
	GROUP BY OrderComp.CompositionID
	ORDER BY SUM(OrderComp.CompositionAmount) DESC LIMIT 1
)