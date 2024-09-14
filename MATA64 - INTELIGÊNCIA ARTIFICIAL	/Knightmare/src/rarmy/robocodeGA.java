package rarmy;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.jgap.*;
import org.jgap.impl.*;

@SuppressWarnings("unchecked")
public class robocodeGA extends FitnessFunction {
	
	public Genotype population;
	public static final int POPULATION_SIZE = 100; 
	public static final int CHROMOSOME_AMOUNT = 2; 
	public static final int TOURNAMENT_SIZE = 3;

	public Map<ChromosomeKey, double[]> chromo_angles = new HashMap<>();

	public Map<ChromosomeKey, double[]> init() throws InvalidConfigurationException  {
        Configuration.reset();
	    Configuration conf = new DefaultConfiguration(); 
	
		setParameters(conf);

		addOperators(conf);

		population = Genotype.randomInitialGenotype(conf);
		
		fillChromoAngles();

		return chromo_angles;
	}

	public Map<ChromosomeKey, double[]> init(IChromosome[] chromosomes) throws InvalidConfigurationException  {
        Configuration.reset();
	    Configuration conf = new DefaultConfiguration(); 

		setParameters(conf);

		addOperators(conf);

		population = new Genotype(conf, new Population(conf, chromosomes));
    
		population.fillPopulation(POPULATION_SIZE - chromosomes.length); 

		fillChromoAngles();
		
		return chromo_angles;
	}

	public void fillChromoAngles(){
		List<IChromosome> chromosomes = population.getPopulation().getChromosomes();
		for (IChromosome chromo : chromosomes) {
			chromo_angles.put(new ChromosomeKey(chromo), new double[CHROMOSOME_AMOUNT]);
		}
	}

	public void setParameters(Configuration conf) throws InvalidConfigurationException{
		conf.setPreservFittestIndividual(false); // don't use elitsim
	    conf.setFitnessFunction(this); // Set fitness function to conf
	    Gene[] sampleGenes = new Gene[ CHROMOSOME_AMOUNT ];
	    sampleGenes[0] = new DoubleGene(conf, -Math.PI/6, Math.PI/6); // stationary targeting
		sampleGenes[1] = new DoubleGene(conf, -Math.PI/6, Math.PI/6); // linear targeting
		IChromosome sampleChromosome = new Chromosome(conf, sampleGenes); // create chromo from genes
		conf.setSampleChromosome(sampleChromosome); // set chromo to conf
		conf.setPopulationSize(POPULATION_SIZE); // create a population
	}
	
	public void addOperators(Configuration conf) throws InvalidConfigurationException{

		// Add Tournament Selector
		TournamentSelector tournamentSelector = new TournamentSelector(conf, TOURNAMENT_SIZE, 0.6);
		tournamentSelector.setDoubletteChromosomesAllowed(false); 
		conf.addNaturalSelector(tournamentSelector, true);	

		// Add Crossover Operator
		CrossoverOperator crossoverOperator = new CrossoverOperator(conf, 0.5);
		conf.addGeneticOperator(crossoverOperator);
		conf.setRandomGenerator(new StockRandomGenerator());
 		
		// Add Mutation Operator
		MutationOperator mutationOperator = new MutationOperator(conf, 15);
		conf.addGeneticOperator(mutationOperator);
	    conf.addGeneticOperator(mutationOperator);

	}


	public Map<ChromosomeKey, double[]> generateNextGen() throws Exception {
		population.evolve();
		List<IChromosome> chromosomes = population.getPopulation().getChromosomes();
		chromo_angles.clear();
		for (IChromosome chromo : chromosomes) {
			chromo_angles.put(new ChromosomeKey(chromo), new double[CHROMOSOME_AMOUNT]); 
		}

		if(chromo_angles.size() <= 2){
			IChromosome[] chromosomeArray = new IChromosome[chromo_angles.size()];
			int i = 0;
			for (ChromosomeKey key : chromo_angles.keySet()) {
				IChromosome chromosome = key.getChromosome();
				chromosomeArray[i] = chromosome;
				i++;
			}
			return init(chromosomeArray);
		}
		return chromo_angles;
	}

	public void setChromosResults(Map<ChromosomeKey, double[]> results){
		chromo_angles = results;
	}

	public double[] getAllele (IChromosome chromosome) {
		int i = 0;
		double[] chromo = new double[CHROMOSOME_AMOUNT];
		for ( Gene gene : chromosome.getGenes() ) {
			chromo[i] = (Double) gene.getAllele(); 
			i++;
		}	
		return chromo;
	}
	
	public double[][] getAllChromosomes(){
		int i = 0;
		double[][] result = new double[CHROMOSOME_AMOUNT][POPULATION_SIZE];
		List<IChromosome> chromosomes = population.getPopulation().getChromosomes();
		System.out.println(chromosomes.size());
		for ( IChromosome chromo : chromosomes ) {
			double[] alleles = getAllele(chromo);
			result[0][i] = alleles[0];
			result[1][i] = alleles[1];
			i++;
		}
		return result;
	}

	public double[] getFittestChromosome(){
		IChromosome chromo = population.getPopulation().determineFittestChromosome();
		return getAllele(chromo);
	}

	@Override
    protected double evaluate( IChromosome chromosome) {
    	double fitness = 0;
		double[] result = chromo_angles.get(new ChromosomeKey(chromosome));
		if(result == null) fitness = 1;
		else fitness = Math.min(Math.abs(result[0]), Math.abs(result[1]));
        return fitness != 0? 1/fitness : 1000;
    }
    
}
