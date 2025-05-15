package saveManager;

import organism.Organism;
import organism.animal.species.Human;
import organism.animal.species.Fox;
import organism.animal.species.Sheep;
import organism.animal.species.Turtle;
import organism.animal.species.Wolf;
import organism.plant.species.*;
import world.World;
import org.json.JSONArray;
import org.json.JSONObject;

import java.io.*;

public class SaveManager {

    public static void saveWorldToFile(World world, String filename) {
        JSONObject j = new JSONObject();
        j.put("width", world.getWidth());
        j.put("height", world.getHeight());
        j.put("turnCounter", world.getTurnCounter());
        j.put("humanAlive", world.isHumanAlive());

        Human human = null;
        for (Organism org : world.getOrganisms()) {
            if (org instanceof Human) {
                human = (Human) org;
                break;
            }
        }
        if (human != null) {
            j.put("humanAbilityActive", human.isAbilityActive());
            j.put("humanAbilityCooldown", human.getAbilityCooldown());
            j.put("humanAbilityDuration", human.getAbilityDuration());
        } else {
            j.put("humanAbilityActive", false);
            j.put("humanAbilityCooldown", 0);
            j.put("humanAbilityDuration", -1);
        }

        JSONArray organismsArray = new JSONArray();
        for (Organism org : world.getOrganisms()) {
            JSONObject orgJson = new JSONObject();
            orgJson.put("className", org.getClass().getSimpleName());
            orgJson.put("x", org.getX());
            orgJson.put("y", org.getY());
            orgJson.put("strength", org.getStrength());
            orgJson.put("initiative", org.getInitiative());
            orgJson.put("age", org.getAge());
            organismsArray.put(orgJson);
        }
        j.put("organisms", organismsArray);

        try (FileWriter file = new FileWriter(filename)) {
            file.write(j.toString(4));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void loadWorldFromFile(World world, String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) sb.append(line);
            JSONObject j = new JSONObject(sb.toString());

            world.clearOrganisms();
            world.setWidth(j.getInt("width"));
            world.setHeight(j.getInt("height"));
            world.setTurnCounter(j.getInt("turnCounter"));
            world.setHumanAlive(j.getBoolean("humanAlive"));

            JSONArray organismsArray = j.getJSONArray("organisms");
            for (int i = 0; i < organismsArray.length(); i++) {
                JSONObject orgJson = organismsArray.getJSONObject(i);
                Organism org = createOrganismFromJson(orgJson, world);
                if (org != null) {
                    org.setStrength(orgJson.getInt("strength"));
                    org.setInitiative(orgJson.getInt("initiative"));
                    org.setAge(orgJson.getInt("age"));
                    world.addOrganism(org);
                }
            }

            // Restore human ability state if human exists
            if (j.getBoolean("humanAlive")) {
                for (Organism org : world.getOrganisms()) {
                    if (org instanceof Human) {
                        Human human = (Human) org;
                        human.setAbilityActive(j.getBoolean("humanAbilityActive"));
                        human.setAbilityCooldown(j.getInt("humanAbilityCooldown"));
                        human.setAbilityDuration(j.getInt("humanAbilityDuration"));
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static Organism createOrganismFromJson(JSONObject orgJson, World world) {
        String className = orgJson.getString("className");
        int x = orgJson.getInt("x");
        int y = orgJson.getInt("y");
        // Add your organism classes here
        switch (className) {
            case "Human": return new Human(x, y, world);
            case "Wolf": return new Wolf(x, y, world);
            case "Fox": return new Fox(x, y, world);
            case "Sheep": return new Sheep(x, y, world);
            case "Turtle": return new Turtle(x, y, world);
            case "Grass": return new Grass(x, y, world);
            case "Dandelion": return new Dandelion(x, y, world);
            case "Belladonna": return new Belladonna(x, y, world);
            case "Guarana": return new Guarana(x, y, world);
            case "SosnowskyHogweed": return new SosnowskyHogweed(x, y, world);
            default: return null;
        }
    }
}