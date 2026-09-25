import argparse

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--test")

    return parser.parse_args()
