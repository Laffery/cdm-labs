method method4(a: array<int>) returns (min: int)
	requires 0 < a.Length
	ensures forall k :: 0 < k < a.Length ==> min <= a[k]
	ensures exists k :: (0 < k < a.Length ==> min == a[k])
{
	var index := 0;
	min := a[0]; // assume first is min
	while index < a.Length
// Add invariants here
	{
		if a[index] <= min { min := a[index]; }
		index := index + 1;
	}
}