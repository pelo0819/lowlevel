import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-p", "--path", default='./uac_test.exe', help="path")
parser.add_argument("-n", "--name", default='./result.txt', help="output file name")
args = parser.parse_args()
path = args.path
file_name = args.name

class FileAnalyzer:
    def __init__(self):
        self.length = 16
        self.row = []
        self.text = []
        self.start_index = 0
        self.maxHeader = 6
        self.maxHexes = 47
        # self.path = 'C:/Users/tobita/Desktop/test.bmp'
        # self.path = './aaa.txt'
        self.path = './uac_test.exe'
        self.output_path = './result.txt'
    
    def set_path(self, p):
        self.path = p 
    
    def set_output_path(self, o):
        self.output_path = o
    
    def print_row(self, out_file):
        head = '{:04X} '.format(self.start_index)
        hexes =  ' '.join([str(n) for n in self.row])
        # texts = ''.join([n for n in self.text])
        texts = ''
        for n in self.text:
            if 0x20 <= ord(n) < 0x7f:
                texts += n.decode('cp932')
            else:
                texts += '.'
        if len(head) < self.maxHeader:
            add = self.maxHeader -len(head)
            for n in range(add):
                head += ' '
        if len(hexes) < self.maxHexes:
            add = self.maxHexes - len(hexes)
            for n in range(add):
                hexes += ' '
        print('%s %s %s' %(head, hexes, texts))
        out_file.write('%s %s %s\n' %(head, hexes, texts))

    
    def analyse(self):
        byte_cnt = 0
        f = open(self.path, 'rb')
        with open(self.output_path, 'w') as out_file:
            while True:
                d = f.read(1)
                byte_cnt += 1
                if len(d) == 0:
                    self.print_row(out_file)
                    break
                else:
                    hex_int = int.from_bytes(d, 'little')
                    hex_str = '{:02X}'.format(hex_int)
                    self.row.append(hex_str)
                    self.text.append(d)
                    if byte_cnt % self.length == 0:
                        self.print_row(out_file)
                        self.row.clear()
                        self.text.clear()
                        self.start_index += self.length   
            f.close()

if __name__ == '__main__':
    analyser = FileAnalyzer()
    analyser.set_path(path)
    analyser.set_output_path(file_name)
    analyser.analyse()