#include <cstdint>
#include "gtest/gtest.h"
#include "../Z80_CPU.h"

using REGISTER_ACCESS_MODE = Z80_CPU::REGISTER_ACCESS_MODE;

Z80_CPU g_cpu;

// Load to register A
TEST(RegisterLoadingTests, loadToA)
{
    const int8_t value = 24;

    g_cpu.AF.lo = value;
    g_cpu.LD_r_r(g_cpu.AF.hi, g_cpu.AF.lo);
    EXPECT_EQ(g_cpu.AF.hi, value);
}

// Load to register B
TEST(RegisterLoadingTests, loadToB)
{
    const int8_t value = 120;

    g_cpu.BC.lo = value;
    g_cpu.LD_r_r(g_cpu.BC.hi, g_cpu.BC.lo);
    EXPECT_EQ(g_cpu.BC.hi, value);
}

// Load to register C
TEST(RegisterLoadingTests, loadToC)
{
    const int8_t value = -1;

    g_cpu.DE.hi = value;
    g_cpu.LD_r_r(g_cpu.BC.lo, g_cpu.DE.hi);
    EXPECT_EQ(g_cpu.BC.lo, value);
}

// Load to register F
TEST(RegisterLoadingTests, loadToF)
{
    const int8_t value = 41;

    g_cpu.HL.lo = value;
    g_cpu.LD_r_r(g_cpu.AF.lo, g_cpu.HL.lo);
    EXPECT_EQ(g_cpu.AF.lo, value);
}

// Load to register D
TEST(RegisterLoadingTests, loadToD)
{
    const int8_t value = 10;

    g_cpu.AF.hi = value;
    g_cpu.LD_r_r(g_cpu.DE.hi, g_cpu.AF.hi);
    EXPECT_EQ(g_cpu.DE.hi, value);
}

// Load to register E
TEST(RegisterLoadingTests, loadToE)
{
    const int8_t value = 15;

    g_cpu.DE.hi = value;
    g_cpu.LD_r_r(g_cpu.DE.lo, g_cpu.DE.hi);
    EXPECT_EQ(g_cpu.DE.lo, value);
}

// Load to register H
TEST(RegisterLoadingTests, loadToH)
{
    const int8_t value = -45;

    g_cpu.BC.hi = value;
    g_cpu.LD_r_r(g_cpu.HL.hi, g_cpu.BC.hi);
    EXPECT_EQ(g_cpu.HL.hi, value);
}

// Load to register L
TEST(RegisterLoadingTests, loadToL)
{
    const int8_t value = 0;

    g_cpu.HL.hi = value;
    g_cpu.LD_r_r(g_cpu.HL.lo, g_cpu.HL.hi);
    EXPECT_EQ(g_cpu.HL.lo, value);
}