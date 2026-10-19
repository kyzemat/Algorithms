#include <iostream>
#include <unordered_map>
#include <optional>
#include <queue>
#include <vector>
using std::optional;
using std::queue;
using std::vector;
using std::unordered_map;
using std::string;

struct Person {
	string Name;
	bool IsSeller;

	Person(const string& name = "", bool seller = false)
		: Name(name), IsSeller(seller) {}
};

struct Node {
	Person person;
	vector<string> neighboors;
};

// Неориентированный граф
class my_graph {
	unordered_map<string, Node> conn;


public:
	my_graph() : conn() {};

	void add_node(const string& name, bool seller = false) {
		if (conn.find(name) == conn.end()) {// Если в хэш таблице нет записей с таким именем - создаем новый узел
			conn[name].neighboors = {}; // Создаем пустой список соседей
			conn[name].person = Person{ name, seller };//Заполняем информацию о нашем человеке
		}
	}

	void add_edge(const string& edge1, const string& edge2) {
		if (conn.find(edge1) == conn.end() || conn.find(edge2) == conn.end()) {
			std::cout << "Невозможно добавить ребро, так как одного или оба узла не существует!";
			return;
		}
		conn[edge1].neighboors.push_back(edge2);//Добавляем соседей обоим узлам
		conn[edge2].neighboors.push_back(edge1);
	}

	optional<string> width_search(const string& name) {

		if (conn.find(name) == conn.end()) {
			return std::nullopt;
		}

		string current;
		queue<string> active;
		unordered_map<string, bool> searched;

		active.push(name);
		searched[name] = true;

		while (!active.empty()) {
			current = active.front();
			active.pop();

			if (conn[current].person.IsSeller) {//Если найденный узел - продавец, то возвращаем имя узла
				return current;
			}
			

			for (const string& a : conn[current].neighboors) {
				if (searched[a]) continue;
				active.push(a);
				searched[a] = true;
			}

		}

		return std::nullopt;//Если не нашли возвращаем nullopt
	}

    optional<string> search_in_depth(const string& name) {
        if (conn.find(name) == conn.end())
            return std::nullopt;

        unordered_map<string, bool> searched;
        return dfs(name, searched);
    }

private:
    optional<string> dfs(const string& name, unordered_map<string, bool>& searched) {
        searched[name] = true;

        if (conn[name].person.IsSeller)
            return name;

        for (const string& person : conn[name].neighboors) {
            if (!searched[person]) {
                auto result = dfs(person, searched);
                if (result.has_value())
                    return result;
            }
        }
        return std::nullopt;
    }

};


int main() {
    setlocale(LC_ALL, "ru");

    // =========================================================
    // Общий граф для тестов BFS и DFS
    //
    //      Саша ── Маша ── Петя (продавец)
    //        │       │
    //      Вася    Коля
    //
    // Продавец только Петя. Он на расстоянии 2 от Саши.
    // =========================================================
    my_graph g;
    g.add_node("Саша");
    g.add_node("Маша");
    g.add_node("Вася");
    g.add_node("Коля");
    g.add_node("Петя", true); // продавец

    g.add_edge("Саша", "Маша");
    g.add_edge("Саша", "Вася");
    g.add_edge("Маша", "Коля");
    g.add_edge("Маша", "Петя");

    // --- Тест 1: поиск продавца от Саши ---
    std::cout << "=== Тест 1: поиск от Саши ===\n";

    if (auto result = g.width_search("Саша"); result)
        std::cout << "  BFS: ближайший продавец — " << *result << "\n"; // Петя
    else
        std::cout << "  BFS: продавцов не найдено\n";

    if (auto result = g.search_in_depth("Саша"); result)
        std::cout << "  DFS: найден продавец — " << *result << "\n";   // Петя
    else
        std::cout << "  DFS: продавцов не найдено\n";

    // --- Тест 2: несуществующий стартовый узел ---
    std::cout << "\n=== Тест 2: несуществующий старт ===\n";

    if (auto result = g.width_search("Несуществующий"); result)
        std::cout << "  BFS: нашли — " << *result << "\n";
    else
        std::cout << "  BFS: nullopt\n";

    if (auto result = g.search_in_depth("Несуществующий"); result)
        std::cout << "  DFS: нашли — " << *result << "\n";
    else
        std::cout << "  DFS: nullopt\n";

    // --- Тест 3: граф без продавцов ---
    std::cout << "\n=== Тест 3: граф без продавцов ===\n";

    my_graph g2;
    g2.add_node("Аня");
    g2.add_node("Боря");
    g2.add_edge("Аня", "Боря");

    if (auto result = g2.width_search("Аня"); result)
        std::cout << "  BFS: нашли — " << *result << "\n";
    else
        std::cout << "  BFS: продавцов нет (nullopt)\n";

    if (auto result = g2.search_in_depth("Аня"); result)
        std::cout << "  DFS: нашли — " << *result << "\n";
    else
        std::cout << "  DFS: продавцов нет (nullopt)\n";

    // --- Тест 4: стартовый узел сам является продавцом ---
    std::cout << "\n=== Тест 4: старт — продавец ===\n";

    my_graph g3;
    g3.add_node("Гена", true);
    g3.add_node("Даша");
    g3.add_edge("Гена", "Даша");

    if (auto result = g3.width_search("Гена"); result)
        std::cout << "  BFS: продавец найден сразу — " << *result << "\n"; // Гена
    else
        std::cout << "  BFS: не нашли\n";

    if (auto result = g3.search_in_depth("Гена"); result)
        std::cout << "  DFS: продавец найден сразу — " << *result << "\n"; // Гена
    else
        std::cout << "  DFS: не нашли\n";

    // --- Тест 5: два продавца, BFS и DFS могут вернуть разных ---
    //
    //      Старт ── Близкий (продавец)
    //        │
    //      Дальний (продавец)
    //
    // BFS вернёт Близкого (он на расстоянии 1).
    // DFS может вернуть Дальнего — зависит от порядка обхода.
    std::cout << "\n=== Тест 5: два продавца ===\n";

    my_graph g4;
    g4.add_node("Старт");
    g4.add_node("Близкий", true);
    g4.add_node("Дальний", true);
    g4.add_edge("Старт", "Близкий");
    g4.add_edge("Старт", "Дальний");

    if (auto result = g4.width_search("Старт"); result)
        std::cout << "  BFS: нашли — " << *result << " (ожидаем Близкий)\n";
    else
        std::cout << "  BFS: не нашли\n";

    if (auto result = g4.search_in_depth("Старт"); result)
        std::cout << "  DFS: нашли — " << *result << " (может быть любой)\n";
    else
        std::cout << "  DFS: не нашли\n";

    // --- Тест 6: длинная цепочка A-B-C-D, продавец в конце ---
    std::cout << "\n=== Тест 6: длинная цепочка ===\n";

    my_graph g5;
    g5.add_node("A");
    g5.add_node("B");
    g5.add_node("C");
    g5.add_node("D", true);
    g5.add_edge("A", "B");
    g5.add_edge("B", "C");
    g5.add_edge("C", "D");

    if (auto result = g5.width_search("A"); result)
        std::cout << "  BFS: нашли — " << *result << " (ожидаем D)\n";
    else
        std::cout << "  BFS: не нашли\n";

    if (auto result = g5.search_in_depth("A"); result)
        std::cout << "  DFS: нашли — " << *result << " (ожидаем D)\n";
    else
        std::cout << "  DFS: не нашли\n";

    // --- Тест 7: ребро с несуществующим узлом ---
    std::cout << "\n=== Тест 7: ребро с несуществующим узлом ===\n";
    g5.add_edge("A", "Z"); // должно вывести предупреждение

    // --- Тест 8: цикл в графе ---
    //
    //      X ── Y
    //      │    │
    //      Z ── W (продавец)
    //
    // Проверяем, что DFS не зациклится.
    std::cout << "\n=== Тест 8: цикл в графе ===\n";

    my_graph g6;
    g6.add_node("X");
    g6.add_node("Y");
    g6.add_node("Z");
    g6.add_node("W", true);
    g6.add_edge("X", "Y");
    g6.add_edge("X", "Z");
    g6.add_edge("Y", "W");
    g6.add_edge("Z", "W");

    if (auto result = g6.width_search("X"); result)
        std::cout << "  BFS: нашли — " << *result << "\n";  // W
    else
        std::cout << "  BFS: не нашли\n";

    if (auto result = g6.search_in_depth("X"); result)
        std::cout << "  DFS: нашли — " << *result << "\n";  // W, без зависания
    else
        std::cout << "  DFS: не нашли\n";

    // =========================================================
// Тест 9: два продавца — один близко, другой глубоко
//
//                        Старт
//                       /     \
//                  Ветка1    Близкий (продавец)
//                    |
//                  Ветка2
//                    |
//                  Ветка3
//                    |
//                Глубокий (продавец)
//
// BFS должен найти Близкого (он на расстоянии 1).
// DFS должен найти Глубокого (он в первой ветке, уходит вглубь).
//
// ВАЖНО: порядок add_edge определяет порядок соседей.
// Сначала добавляем ребро Старт–Ветка1, потом Старт–Близкий.
// Тогда DFS пойдёт в Ветка1 → Ветка2 → Ветка3 → Глубокий.
// =========================================================
    std::cout << "\n=== Тест 9: BFS vs DFS — два продавца ===\n";

    my_graph g7;
    g7.add_node("Старт");
    g7.add_node("Ветка1");
    g7.add_node("Ветка2");
    g7.add_node("Ветка3");
    g7.add_node("Близкий", true);   // продавец на расстоянии 1
    g7.add_node("Глубокий", true);  // продавец на расстоянии 4

    // Порядок важен: сначала глубокая ветка, потом близкий продавец
    g7.add_edge("Старт", "Ветка1");     // ← первый сосед Старта
    g7.add_edge("Старт", "Близкий");    // ← второй сосед Старта

    g7.add_edge("Ветка1", "Ветка2");
    g7.add_edge("Ветка2", "Ветка3");
    g7.add_edge("Ветка3", "Глубокий");

    if (auto result = g7.width_search("Старт"); result)
        std::cout << "  BFS: нашли — " << *result << " (ожидаем Близкий)\n";
    else
        std::cout << "  BFS: не нашли\n";

    if (auto result = g7.search_in_depth("Старт"); result)
        std::cout << "  DFS: нашли — " << *result << " (ожидаем Глубокий)\n";
    else
        std::cout << "  DFS: не нашли\n";


    return 0;
}