import argparse

def parse_args():
    parser = argparse.ArgutmentParser()
    parser.add("--")

    return parser.parse_args()
