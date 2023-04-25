SELECT SUM(FlowersAmount*Price) as CompPrice FROM FlowerComp
INNER JOIN Composition ON CompositionID = Composition.ID  AND Composition.ID == 10
INNER JOIN Flower ON FlowerComp.FlowerID = Flower.ID