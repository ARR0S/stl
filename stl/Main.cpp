#include "Container.h"
#include "Algorithms.h"
#include <iostream>
#include <string>
struct Goods
{
    uint32_t m_id;
    std::string m_name;
    std::string m_manufacturer;
    std::string m_warehouse_address;
    double m_weight;

    bool operator==(const Goods& rhs) const
    {
        return m_id == rhs.m_id &&
            m_name == rhs.m_name &&
            m_manufacturer == rhs.m_manufacturer &&
            m_warehouse_address == rhs.m_warehouse_address &&
            m_weight == rhs.m_weight;
    }

    Goods& operator=(const Goods& other)
    {
        if (this != &other) {
            m_id = other.m_id;
            m_name = other.m_name;
            m_manufacturer = other.m_manufacturer;
            m_warehouse_address = other.m_warehouse_address;
            m_weight = other.m_weight;
        }
        return *this;
    }
};
template <typename Key, typename Value, typename Compare>
void SortUnorderedMapByValue(UnorderedMap<Key, Value>& map, Compare comp)
{
    if (map.size() >= 2)
    {
        std::vector<std::pair<Key, Value>> sortedVector(map.begin(), map.end());
        Sort(sortedVector.begin(), sortedVector.end(), comp);
        // Вывод отсортированных элементов
        for (const auto& pair : sortedVector) {
            const Goods& goods = pair.second;
            std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
                << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
                << ", Weight: " << goods.m_weight << "\n";
        };
    }
    else
    {
        forEach(map.begin(), map.end(), [](auto& item) {
            const Goods& goods = item.second;
            std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
                << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
                << ", Weight: " << goods.m_weight << "\n";
            });
    }
}
struct ManufacturerPredicate
{
    ManufacturerPredicate(const std::string& manufacturer) : manufacturer_(manufacturer) {}

    bool operator()(const std::pair<uint32_t, Goods>& item) const
    {
        const Goods& goods = item.second;
        return goods.m_manufacturer == manufacturer_;
    }

    std::string manufacturer_;
};
template <typename Key, typename Value, typename Predicate>
void CopyUnorderedMapByValue(UnorderedMap<Key, Value>& source, UnorderedMap<Key, Value>& dest, Predicate pred)
{
    std::vector<std::pair<Key, Value>> vec(source.size());
    copyIf(source.begin(), source.end(), vec.begin(), pred);
    for (auto it=vec.begin();it!=vec.end(); ++it) 
    {
        if ((*it).first == 0)
        {
            break;
        };
        dest.insert(std::move(*it));
        };
}
int main()
{
    // Создание контейнера товаров cont_1 с помощью std::initializer_list
    UnorderedMap<uint32_t, Goods> cont_1 = {
        { 1, { 1, "Mandarin", "Manufacturer 1", "Address 1", 1.5 } },
        { 2, { 2, "Apple", "Manufacturer 2", "Address 2", 2.5 } },
        { 3, { 3, "Apricot", "Manufacturer 3", "Address 3", 3.5 } }
    };
    // Вывод содержимого контейнера cont_1
    std::cout << "Container cont_1:\n";
    forEach(cont_1.begin(), cont_1.end(), [](auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_1.size();
    // Создание нескольких объектов и добавление в контейнер cont_2
    Goods goods1{ 4, "Dron", "Manufacturer 4", "Address 4", 4.5 };
    Goods goods2{ 5, "Applepen 5", "Manufacturer 5", "Address 5", 5.5 };
    Goods goods3{ 6, "Cerop 6", "Manufacturer 6", "Address 6", 6.5 };

    UnorderedMap<uint32_t, Goods> cont_2;
    cont_2.insert({ 4, goods1 });
    cont_2.insert({ 5, std::move(goods2) });
    cont_2.insert({ 6, goods3 });
    //Вывод содержимого контейнера cont_2
    std::cout << "\n\nContainer cont_2:\n";
    forEach(cont_2.begin(), cont_2.end(), [](auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_2.size();
    /*Используя диапазонную версию insert вставить cont_2 в середину cont_1.
     Вывести содержимое контейнера, используя алгоритм forEach и лямбда-функцию печати.
     Данная функция не реализована в моем варианте*/
     //Сортировка контейнера cont_1 по названию товара
    std::cout << "\n\nSorted by name container cont_1:\n";
    SortUnorderedMapByValue(cont_1, [](auto& item1, auto& item2) {
        return item1.second.m_name < item2.second.m_name;
        });
    // Поиск первого товара с весом из заданного диапазона
    double minWeight = 2.0;
    double maxWeight = 5.0;
    auto found = findIf(cont_1.begin(), cont_1.end(), [minWeight, maxWeight](auto& item) {
        const Goods& goods = item.second;
        return goods.m_weight >= minWeight && goods.m_weight <= maxWeight;
        });
    std::cout << "\nFound goods with weight in range (" << minWeight << " - " << maxWeight << "):\n";
    if (found != cont_1.end()) {
        const Goods& goods = (*found).second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";

        // Изменение адреса склада
        found->m_warehouse_address = "New Address";
        // Вывод содержимого контейнера cont_1 после изменения адреса склада
        std::cout << "\nContainer cont_1 after modifying the warehouse address:\n";
        forEach(cont_1.begin(), cont_1.end(), [](const auto& item) {
            const Goods& goods = item.second;
            std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
                << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
                << ", Weight: " << goods.m_weight << "\n";
            });
        std::cout << "Size of container: " << cont_1.size();
    }
    else std::cout << "No such elements\n";

    // Копирование товаров одного производителя в новый контейнер cont_3
    std::string manufacturer = "Manufacturer 2";
    UnorderedMap<uint32_t, Goods> cont_3;
    CopyUnorderedMapByValue(cont_1, cont_3, ManufacturerPredicate(manufacturer));

    // Вывод содержимого контейнера cont_3
    std::cout << "\n\nContainer cont_3 (Goods with manufacturer '" << manufacturer << "'):\n";
    forEach(cont_3.begin(), cont_3.end(), [](const auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_3.size();
    cont_2.erase(++cont_2.begin());
    std::cout << "\n\nContainer cont_2 after deletion 2nd with iterator element:\n";
    forEach(cont_2.begin(), cont_2.end(), [](auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_2.size();
    cont_2.erase(5);
    std::cout << "\n\nContainer cont_2 after deletion with key element:\n";
    forEach(cont_2.begin(), cont_2.end(), [](auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_2.size();
    cont_2.clear();
    std::cout << "\n\nContainer cont_2 after clear:\n";
    forEach(cont_2.begin(), cont_2.end(), [](auto& item) {
        const Goods& goods = item.second;
        std::cout << "ID: " << goods.m_id << ", Name: " << goods.m_name << ", Manufacturer: "
            << goods.m_manufacturer << ", Warehouse Address: " << goods.m_warehouse_address
            << ", Weight: " << goods.m_weight << "\n";
        });
    std::cout << "Size of container: " << cont_2.size();
    return 0;
}
