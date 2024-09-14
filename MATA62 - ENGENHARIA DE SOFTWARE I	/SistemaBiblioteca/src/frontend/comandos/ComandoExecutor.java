package SistemaBiblioteca.src.frontend.comandos;

import java.util.HashMap;

public class ComandoExecutor {
    private HashMap<String, Comando> comandos = new HashMap<String, Comando>();

    public ComandoExecutor(){
        initComandos();
    }

    private void initComandos(){
        this.comandos.put("dev", new Devolver());
        this.comandos.put("emp", new RealizarEmprestimo());
        this.comandos.put("liv", new ConsultarLivro());
        this.comandos.put("ntf", new ConsultarNotificacoes());
        this.comandos.put("obs", new RegistrarObservador());
        this.comandos.put("res", new FazerReserva());
        this.comandos.put("sai", new SairSistema());
        this.comandos.put("usu", new ConsultarUsuario());
    }

    public void executarComando(String cmd, int ... params) throws IllegalArgumentException, InterruptedException {
        if (!this.comandos.containsKey(cmd)) {
            throw new IllegalArgumentException("O comando '" + cmd + "' é inválido.");
        }

        Comando comando = comandos.get(cmd);
        comando.executar(params);
    }
}
