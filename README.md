<div align="center">
  <img src="https://github.com/szabo-krisztian/SortItOut/raw/master/gif/merge_sort.gif" alt="Merge sort">
</div>

# Sort it out

Sorting algorithms visualized with simple animation using the SDL2 C library. Due to the abstraction layers, it is quite easy to add new algorithms to the code, each implementing the abstract `Algorithm` class:

```cpp
class Algorithm
{
public:
    Algorithm(volatile bool &isAppRunning) : m_isAppRunning(isAppRunning) {}
    virtual ~Algorithm() = default;

    virtual void Sort(SyncVector &numbers) = 0;

protected:
    volatile bool &m_isAppRunning;
};
```

Few parameters can be changed in the `main.cpp` file:
```cpp
int main(int argc, char* argv[])
{
    tlr::AppConfig appConfig =
    {
        .windowWidth = 800,
        .windowHeight = 600,
        .windowPosX = 100,
        .windowPosY = 100,
        .numberCount = 100,
        .swapTimeInMillis = 5
    };

    tlr::App app(appConfig);
    app.Run();
    
    return 0;
}
```