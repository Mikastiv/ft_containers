# ft_containers

Reimplementation of std::vector, std::stack, std::map and std::set according to the C++98 standard

## Performance vs LLVM's libc++

#### Vector

|          function          |  ft::vector  |  std::vector  |   %diff   |
|----------------------------|--------------|---------------|-----------|
| assign                     | 3361ms       | 3201ms        |    +5.00% |
| assignment                 | 5193ms       | 4992ms        |    +4.03% |
| assign_range               | 5780ms       | 5388ms        |    +7.28% |
| ctor_copy                  | 2787ms       | 3404ms        |   -18.13% |
| ctor_range                 | 3257ms       | 3865ms        |   -15.73% |
| ctor_size                  | 1980ms       | 2048ms        |    -3.32% |
| dtor                       | 381ms        | 340ms         |   +12.06% |
| erase                      | 7988ms       | 8136ms        |    -1.82% |
| erase_range                | 2073ms       | 2176ms        |    -4.73% |
| insert                     | 15263ms      | 14787ms       |    +3.22% |
| insert_range               | 3360ms       | 3492ms        |    -3.78% |
| insert_size                | 12479ms      | 9125ms        |   +36.76% |
| pop_back                   | 1821ms       | 1705ms        |    +6.80% |
| push_back                  | 21625ms      | 21575ms       |    +0.23% |
| resize                     | 1621ms       | 1651ms        |    -1.82% |

#### Map

|          function          |  ft::vector  |  std::vector  |   %diff   |
|----------------------------|--------------|---------------|-----------|
| assignment                 | 14099ms      | 11042ms       |   +27.69% |
| clear                      | 1378ms       | 1409ms        |    -2.20% |
| ctor_copy                  | 13172ms      | 11538ms       |   +14.16% |
| ctor_range                 | 14071ms      | 14669ms       |    -4.08% |
| dtor                       | 1099ms       | 1111ms        |    -1.08% |
| equal_range                | 10778ms      | 10643ms       |    +1.27% |
| erase                      | 9571ms       | 9437ms        |    +1.42% |
| erase_range                | 1633ms       | 1728ms        |    -5.50% |
| find                       | 10978ms      | 10372ms       |    +5.84% |
| index_operator             | 8655ms       | 8512ms        |    +1.68% |
| insert                     | 8387ms       | 8347ms        |    +0.48% |
| insert_hint                | 14692ms      | 14308ms       |    +2.68% |
| insert_range               | 13160ms      | 11953ms       |   +10.10% |
| lower_bound                | 10634ms      | 12790ms       |   -16.86% |
| upper_bound                | 13352ms      | 13201ms       |    +1.14% |

#### Set

|          function          |  ft::vector  |  std::vector  |   %diff   |
|----------------------------|--------------|---------------|-----------|
| assignment                 | 14141ms      | 12431ms       |   +13.76% |
| clear                      | 1381ms       | 1365ms        |    +1.17% |
| ctor_copy                  | 12758ms      | 12122ms       |    +5.25% |
| ctor_range                 | 13995ms      | 14882ms       |    -5.96% |
| dtor                       | 1120ms       | 1160ms        |    -3.45% |
| equal_range                | 12374ms      | 12102ms       |    +2.25% |
| erase                      | 9543ms       | 9548ms        |    -0.05% |
| erase_range                | 1721ms       | 1749ms        |    -1.60% |
| find                       | 13249ms      | 11574ms       |   +14.47% |
| insert                     | 8765ms       | 8685ms        |    +0.92% |
| insert_hint                | 13267ms      | 13635ms       |    -2.70% |
| insert_range               | 12803ms      | 11885ms       |    +7.72% |
| lower_bound                | 10005ms      | 12248ms       |   -18.31% |
| upper_bound                | 11343ms      | 10394ms       |    +9.13% |
