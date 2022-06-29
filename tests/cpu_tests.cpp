#include <cstdint>
#include "gtest/gtest.h"
#include "../Z80_CPU.h"

using REGISTER_ACCESS_MODE = Z80_CPU::REGISTER_ACCESS_MODE;

Z80_CPU g_cpu;

// Load to register A
TEST(RegisterLoadingTests, loadToA)
{
    const int8_t value = 24;

    g_cpu.F = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.A, g_cpu.F);
    EXPECT_EQ(g_cpu.A, value);
}

// Load to register B
TEST(RegisterLoadingTests, loadToB)
{
    const int8_t value = 120;

    g_cpu.C = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.B, g_cpu.C);
    EXPECT_EQ(g_cpu.B, value);
}

// Load to register C
TEST(RegisterLoadingTests, loadToC)
{
    const int8_t value = -1;

    g_cpu.D = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.C, g_cpu.D);
    EXPECT_EQ(g_cpu.C, value);
}

// Load to register F
TEST(RegisterLoadingTests, loadToF)
{
    const int8_t value = 41;

    g_cpu.L = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.F, g_cpu.L);
    EXPECT_EQ(g_cpu.F, value);
}

// Load to register D
TEST(RegisterLoadingTests, loadToD)
{
    const int8_t value = 10;

    g_cpu.A = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.D, g_cpu.A);
    EXPECT_EQ(g_cpu.D, value);
}

// Load to register E
TEST(RegisterLoadingTests, loadToE)
{
    const int8_t value = 15;

    g_cpu.D = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.E, g_cpu.D);
    EXPECT_EQ(g_cpu.E, value);
}

// Load to register H
TEST(RegisterLoadingTests, loadToH)
{
    const int8_t value = -45;

    g_cpu.B = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.H, g_cpu.B);
    EXPECT_EQ(g_cpu.H, g_cpu.B);
}

// Load to register L
TEST(RegisterLoadingTests, loadToL)
{
    const int8_t value = 0;

    g_cpu.H = value;
    g_cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER(g_cpu.L, g_cpu.H);
    EXPECT_EQ(g_cpu.L, value);
}