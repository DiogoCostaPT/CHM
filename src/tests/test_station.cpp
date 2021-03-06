//
// Canadian Hydrological Model - The Canadian Hydrological Model (CHM) is a novel
// modular unstructured mesh based approach for hydrological modelling
// Copyright (C) 2018 Christopher Marsh
//
// This file is part of Canadian Hydrological Model.
//
// Canadian Hydrological Model is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Canadian Hydrological Model is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Canadian Hydrological Model.  If not, see
// <http://www.gnu.org/licenses/>.
//


#include "../station.hpp"
#include "gtest/gtest.h"

class StationTest : public testing::Test
{
protected:


    virtual void SetUp()
    {
        logging::core::get()->set_logging_enabled(false);
        ASSERT_NO_THROW(s1.open("test_met_data.txt"));
    }

    station s0;
    station s1;
};


//tests for proper default init
TEST_F(StationTest, DefaultInit)
{
    EXPECT_EQ(0, s0.x());
    EXPECT_EQ(0, s0.y());
    EXPECT_EQ(0, s0.z());
}

//Test that a file that exist doesn't throw
//Test that the internal iterator doesn't throw on dereference
TEST_F(StationTest, ExistFileOpens)
{
    ASSERT_NO_THROW(s0.open("test_met_data.txt"));
    ASSERT_NO_THROW(s0.now());
}

//Test that opening a file that doesn't exist throws
TEST_F(StationTest, NoExistFileOpens)
{
    ASSERT_ANY_THROW(s0.open("file_that_doesnt_exist.txt"));
}

//ensure that the iterators properly return end())
TEST_F(StationTest, ItrNext)
{
    EXPECT_EQ(true, s1.next());
}

//ensure we read in the right thing
TEST_F(StationTest, FileContents)
{
    ASSERT_DOUBLE_EQ(-8.1, s1.get("t"));
    ASSERT_DOUBLE_EQ(40.282, s1.get("rh"));
    ASSERT_DOUBLE_EQ(0.647, s1.get("u"));
    ASSERT_DOUBLE_EQ(0.1031, s1.get("p"));
    ASSERT_DOUBLE_EQ(112.101, s1.get("Qsi"));
    ASSERT_DOUBLE_EQ(3.859, s1.get("T_g"));

    EXPECT_EQ(true, s1.next());

    ASSERT_DOUBLE_EQ(14.268, s1.get("t"));
    ASSERT_DOUBLE_EQ(21.739, s1.get("rh"));
    ASSERT_DOUBLE_EQ(1.850, s1.get("u"));
    ASSERT_DOUBLE_EQ(0.0000, s1.get("p"));
    ASSERT_DOUBLE_EQ(650.219, s1.get("Qsi"));
    ASSERT_DOUBLE_EQ(4.687, s1.get("T_g"));
    
}

//test we are returning the correct length
TEST_F(StationTest, Length)
{
    EXPECT_EQ(2, s1.timeseries_length());
}

