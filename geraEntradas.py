import random

def gerar_entrada():
    n = random.randint(100, 1000)
    m = random.randint(100, 1000)
    k = random.randint(10, 100)
    coordenadas = [(random.uniform(0, 1000), random.uniform(0, 1000)) for _ in range(n)]
    arestas = [(random.randint(0, n-1), random.randint(0, n-1)) for _ in range(m)]
    portais = [(random.randint(0, n-1), random.randint(0, n-1)) for _ in range(k)]
    energia = random.uniform(1, 100)
    maxPortais = random.randint(1, 10)
    
    return n, m, k, coordenadas, arestas, portais, energia, maxPortais

def main():
    num_execucoes = 10  
    with open('entrada.txt', mode='w') as file:
        file.write(f"{num_execucoes}\n")
        for _ in range(num_execucoes):
            n, m, k, coordenadas, arestas, portais, energia, maxPortais = gerar_entrada()
            file.write(f"{n} {m} {k}\n")
            for coord in coordenadas:
                file.write(f"{coord[0]} {coord[1]}\n")
            for aresta in arestas:
                file.write(f"{aresta[0]} {aresta[1]}\n")
            for portal in portais:
                file.write(f"{portal[0]} {portal[1]}\n")
            file.write(f"{energia} {maxPortais}\n")

if __name__ == "__main__":
    main()
