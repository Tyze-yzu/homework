作業的 Vector 與 List 都是複製之前的就可以了，iterator 基哥有幫忙寫。<br>
這次花很多時間在 Hugeinteger 這個 class 上面，卡著一堆 operator<< 的 bug。<br>
除了乘法以外的 functions 呢，我之前就是用 iterator 寫的，改起來很快。<br>
乘法如果要用 iterator 作的話，上次的做法就行不通了，所以完全大改。

---

列出幾個「有動過基哥原始 code 」的地方，有緣再來解吧！

```cpp
// origin
friend ostream& operator<<( ostream &output, HugeInteger< T > &hugeInteger );

// fixed
friend ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger );
```
```cpp
// origin
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger &op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger remainder = (*this) - (quotient * op2);
	return remainder;
};

// fixed
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger &op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger tmp = quotient * op2;
	HugeInteger remainder = (*this) - tmp;
	return remainder;
};
```
---
還有些我亂改出來還沒看懂的 code，都是照著原本改，但是都會噴錯。有空再想，累了。<br>

- 借位
```cpp
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 ) 
{
   HugeInteger< T > difference(*this);
   for (T::reverse_iterator tmp = difference.integer.rbegin(), tmp2 = (++difference.integer.rbegin()); tmp2 != difference.integer.rend(); ++tmp, ++tmp2) {
	   (*tmp)--;
	   (*tmp2) += 10;
   }
   // 這借位有問題 有緣再找bug
   
   // for (T::reverse_iterator tmp = difference.integer.rbegin(); tmp != (++difference.integer.rend()); ++tmp) {
   //    (*tmp)--;
   //    (*(--tmp)) += 10;
   //    ++tmp;
   // }
   ...
```
- 去掉 0
```cpp
vector<T>::iterator it = product.integer.end() - 1;
	while (*it == 0 && it != product.integer.begin())
	{
		product.integer.pop_back();
		it--;
	}
```