# RotateArrayRight

Roterar arrayen ett steg åt höger.

Start array:

`[1, 2, 3, 4]`

Roterad 1 gång:

`[2, 1, 3, 4]`

---

# RotateArrayLeft

Roterar arrayen ett steg år vänster

Start array:

`[1, 2, 3, 4]`

Roterad 1 gång:

`[2, 3, 4, 1]`

---

# Scroll funktionaliteten

`LCD` kommer att se ut så här från början

+----------------------+
|> Easy                |
|  Medium              |
+----------------------+

Sedan ska man skrolla ner genom att rotera arrayen ett steg med `rotateArrayRight`. Då ser menyn ut så här

+----------------------+
|> Medium              |
|  Hard                |
+----------------------+

Arrayen roteras och man kör `LCD`.clear för att ränsa displayen. Sedan skriver man ut exakt samma sak igen, fast nu ser arrayen annorlunda ut vilket betyder att `LCD` skriver ut det som att man har skrollat. Pilen sitter på Hard vilket är `array[0]` nu när den är roterad. Om man nu drar ner pilen till Pro sitter den på `array[1]`. Går man ett till steg neråt skrollar den igen och ser ut så här:

+----------------------+
|> Hard                |
|  Easy                |
+----------------------+

Då är Pro `array[0]` och Easy `array[1]` och så håller man på så. Om man vill skrolla tillbaka använder man `rotateArrayLeft`. Samma princip med indexes gäller.