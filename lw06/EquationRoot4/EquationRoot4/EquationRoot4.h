#pragma once

// ¬ычисл€ем корни кубического уравнени€ ax^4 + bx^3 + cx^2 + dx + e = 0
std::vector<double> Solve4(double a, double b, double c, double d, double e);
void PrintRoots(const std::vector<double>& roots, std::ostream &output);
