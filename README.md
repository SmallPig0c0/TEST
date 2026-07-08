# BFS Graph Visualization

這個專案使用 C++ 實作無向圖的 BFS（Breadth-First Search，廣度優先搜尋），並將搜尋結果輸出成 Graphviz 可讀取的 `graph.dot` 檔案，方便進一步轉成圖片觀察圖的結構與 BFS 結果。

## 功能

- 讀入一張無向圖
- 從指定起點執行 BFS
- 輸出 BFS 拜訪順序
- 輸出每個節點到起點的距離
- 產生 `graph.dot` 視覺化檔案
- 用紅色粗邊標示 BFS tree edge
- 用節點顏色標示 BFS 距離

## 檔案說明

```text
main.cpp    BFS 主程式
graph.dot   程式執行後產生的 Graphviz DOT 檔案
```

## 編譯方式

在專案資料夾中執行：

```powershell
g++ main.cpp -o main.exe
```

## 執行方式

```powershell
.\main.exe
```

程式會從標準輸入讀取資料。

## 輸入格式

```text
n m start
u1 v1
u2 v2
...
um vm
```

其中：

- `n`：節點數量，節點編號為 `1` 到 `n`
- `m`：邊的數量
- `start`：BFS 起點
- `ui vi`：代表一條無向邊，連接 `ui` 和 `vi`

## 範例輸入

```text
5 5 1
1 2
1 3
2 4
3 4
4 5
```

## 範例輸出

```text
BFS order: 1 2 3 4 5
Distance from 1:
1: 0
2: 1
3: 1
4: 2
5: 3
Visualization DOT file written to graph.dot
```

## 視覺化

程式執行後會產生：

```text
graph.dot
```

如果已安裝 Graphviz，可以使用以下指令將 DOT 檔轉成 PNG 圖片：

```powershell
dot -Tpng graph.dot -o graph.png
```

產生的 `graph.png` 會顯示：

- 節點標籤：節點編號與距離，例如 `1\nd=0`
- 紅色粗邊：BFS 搜尋樹中的邊
- 一般邊：原圖中存在但不是 BFS tree edge 的邊

## 顏色說明

| 距離 | 顏色 |
|---|---|
| `0` | gold |
| `1` | lightblue |
| `2` | lightgreen |
| `3` | lightpink |
| `-1` | lightgray |
| 其他 | white |

其中 `dist = -1` 表示該節點無法從起點到達。

## BFS 時間複雜度

使用 adjacency list 儲存圖時，BFS 的時間複雜度為：

```text
O(n + m)
```

其中：

- `n` 是節點數量
- `m` 是邊的數量

原因是每個節點最多進入 queue 一次，每條邊最多被檢查常數次。
