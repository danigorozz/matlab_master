function datos = generar_grupos(margenes, n_grupos, n_puntos, desv)

    if nargin < 3, error(message('Faltan argumentos')), end
    if nargin == 3, desv=0.25; end

    [r,q] = size(margenes);
    minv = min(margenes')';
    maxv = max(margenes')';
    datos = rand(r,n_grupos) .* ((maxv-minv) * ones(1,n_grupos)) + (minv * ones(1,n_grupos));
    t = n_grupos*n_puntos;
    datos = repmat(datos,1,n_puntos) + randn(r,t)*desv;

end

