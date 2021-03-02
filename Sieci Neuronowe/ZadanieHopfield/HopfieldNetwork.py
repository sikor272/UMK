import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt
import matplotlib.cm as cm


class HopfieldNetwork(object):
    def __init__(self, N):
        self.N = N
        self.weights = np.zeros((self.N, self.N))
        self.P = 0
        self.iterations = 100
        self.e = 0

    def little_dynamics(self, state):
        self.e = self.energy(state)
        for _ in tqdm(range(self.iterations)):
            state = np.sign(self.weights @ state)
            e_after = self.energy(state)
            if e_after == self.e:
                return state
            self.e = e_after
        return state

    def run_dynamics(self, state, dtype='glauber'):
        if dtype == 'glauber':
            return self.glauber_dynamic(state)  # async
        else:
            return self.little_dynamics(state)  # sync

    def glauber_dynamic(self, state):
        self.e = self.energy(state)
        for _ in tqdm(range(self.iterations)):
            for i in range(self.iterations * 3):
                idx = np.random.randint(0, self.N)
                state[idx] = np.sign(self.weights[idx].T @ state)
                # self.weights[idx] @ state ?? to wtedy w little transponowac
            e_after = self.energy(state)
            if e_after == self.e:
                return state
            self.e = e_after
        return state

    def plot_weights(self):
        plt.figure(figsize=(6, 5))
        plt.colorbar(plt.imshow(self.weights, cmap=cm.coolwarm))
        plt.tight_layout()
        plt.savefig("weights.png")
        plt.show()

    # i = np.random.randint(0, self.N)
    # a = np.matmul(self.weights[i, :], state)
    # if a < 0:
    #     state[i] = -1
    # else:
    #     state[i] = 1
    # return state

    def energy(self, state):
        return -0.5 * state @ self.weights @ state

    def training(self, training_data):
        self.P = len(training_data)
        W = np.zeros((self.N, self.N))
        rho = np.sum([np.sum(t) for t in training_data]) / (self.P * self.N)
        # Regula hebba
        for i in tqdm(range(self.P)):
            t = training_data[i] - rho
            W += np.outer(t, t)

        diagW = np.diag(np.diag(W))
        W = W - diagW
        W /= self.P

        # diag = [W[i][i] for i in range(len(W))]
        # print(diag)
        self.weights = W.copy()

        # for p in range(self.P):
        #   self.weights +=
        # self.P = len(training_data)
        # for i in tqdm(range(self.N)):
        #     for j in range(self.N):
        #         if i != j:
        #             for p in range(self.P):
        #                 self.weights[i, j] += np.array(training_data)[p, i] * np.array(training_data)[p, j]
        # self.weights /= self.N

    def hamming(self, state, training_data):
        test_size = 10
        hamming_distance = np.zeros((test_size, self.P))
        state_copy = state.copy()
        h = np.zeros(self.N)
        # for iteration in tqdm(range(test_size)):
        #     state_copy = self.run_dynamics(state_copy).copy()
        #     state = state_copy.copy()
        #     for i in range(self.N):
        #         i = np.random.randint(0, self.N)
        #         h[i] = 0
        #         for j in range(self.N):
        #             h[i] += self.weights[i, j] * state[j]
        #         state = np.where(h < 0, -1, 1)
        #     for p in range(self.P):
        #         hamming_distance[iteration, p] = self.N - (training_data[p] - state != 0).sum()
        # plt.plot(hamming_distance)
        # plt.xlabel("Iteration")
        # plt.ylabel("Distance")
        # plt.legend([f for f in listdir("Images") if isfile(join("Images", f))])
        # plt.show()
        return state_copy
