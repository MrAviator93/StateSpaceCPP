clear all
A = [0 1; -3 -2];
B = [0; 1];
C = [1 0];
D = [0];

Q = [1 0; 0 1];
R = 1;
K = lqr(A,B,Q,R);

%This is pure system
g = ss(A,B,C,D);

%mofified control law
g2 = ss((A-B*K),B,C,D);

ltiview(g)
ltiview(g2)

%Initial conditions
X0=[0; 0];

%u is desired condition for 2 by 2 A matrix,
%we have only a single controllable variable.
u=[1]; 

t=0;                        %Initial time
dt = 0.01;                    %Step size
tsim = 160.0;                   %Simulation time
n = round((tsim-t)/dt);       %Number of Iterations

t = t:dt:tsim;
X = zeros(2, length(t));
Y = zeros(2, length(t));
X(:,1) = X0;

for i = 2:length(t)
    X(:, i) = X(:,i - 1) + dt * (A * X(:,i - 1) + B * u);
end

for i = 1:length(t)
    Y(:, i) = C * X(:, i);
end

%For copying into excel
t2 = t';
X2 = X';
Y2 = Y';