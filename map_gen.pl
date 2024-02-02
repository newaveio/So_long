#!/usr/bin/env perl
use strict;
use warnings;

# Define the density
my $enemy_density = 0.05;
my $wall_density = 0.2;
my $collectible_density = 0.1;

# Define the size of the map
my $rows = 3 + int(rand(18));
my $cols = 3 + int(rand(18));

# Create an empty 2D array
my @map;

for my $i (0..$rows-1)
{
    for my $j (0..$cols-1)
    {
        if ($i == 0 || $i == $rows-1 || $j == 0 || $j == $cols-1)
        {
            $map[$i][$j] = 1;
        }
        else
        {
            my $rand_num = rand();
            if ($rand_num < $enemy_density)
            {
                $map[$i][$j] = 'X';
            }
            elsif ($rand_num < $enemy_density + $wall_density)
            {
                $map[$i][$j] = '1';
            }
            elsif ($rand_num < $enemy_density + $wall_density + $collectible_density)
            {
                $map[$i][$j] = 'C';
            }
            else
            {
                $map[$i][$j] = '0';
            }
        }
    }
}

# Generate Player and Exit
my $player_x;
my $player_y;
do {
    $player_x = 1 + int(rand($cols-2));
    $player_y = 1 + int(rand($rows-2));
} while ($map[$player_y][$player_x] eq 'C');
$map[$player_y][$player_x] = 'P';

my $exit_x;
my $exit_y;
do {
    $exit_x = 1 + int(rand($cols-2));
    $exit_y = 1 + int(rand($rows-2));
} while ($map[$exit_y][$exit_x] ne '0' && $map[$exit_y][$exit_x] ne '1');
$map[$exit_y][$exit_x] = 'E';

my $filename = "rand_map.ber";

# Open file for writting
open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

for my $i (0..$rows-1)
{
    for my$j (0..$cols-1)
    {
        print $fh $map[$i][$j];
    }
    printf $fh "\n" if $i != $rows-1;
}

close $fh;