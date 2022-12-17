sys = linmod('pendulo');
nopts=100;
f = logspace(-2, 10, nopts);
G = zeros(1, nopts);
A = sys.a;
B = sys.b;
C = sys.c;
D = sys.d;
for i = 1:nopts
    G(i) = -C*(2*pi*1i*f(i)*eye(size(A)) - A)^(-1)*B - D;
end
subplot(211), semilogx(f, 20*log10(abs(G))), grid
ylabel('Magnitude (db)')
subplot(212), semilogx(f, 180/pi*unwrap(angle(G))), grid
ylabel('Phase (degrees)')
xlabel('Frquency (Hz)')