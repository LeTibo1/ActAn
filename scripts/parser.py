import argparse

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--file", type=str)

    return parser.parse_args()
