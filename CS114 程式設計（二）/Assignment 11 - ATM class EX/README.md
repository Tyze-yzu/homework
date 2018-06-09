# 改動

- getMovie return type. (Movie -> Movie&)
- sessionTime (char arr\[24\]\[2\] -> char arr\[24\]\[3\])

# 方式

改上學期的 code，在 ref 底下自己看。

# 已知問題

記一些 bug 給學霸們修

- 每次 execute function 回來之後，都會跑一次 input error。（看了很煩，所以我註解掉了）

  > main 的 inputInteger cin.getline 改 cin >> （感謝 [Tomy](http://github.com/tomy0000000) ）

- 一開始沒 newMember 的話好像會噴錯。（就是帳密錯的時候，不過應該是基哥的問題）

  > vector< Member >::iterator MemberDatabase::getMember 如果找不到，要 return members.end() （感謝我自己 :D）

- 偷懶沒寫 void Booking::displayBooking( MovieDatabase &movieDatabase )

  > 感謝品元帥帥提醒，雖然沒有給我 code 抄