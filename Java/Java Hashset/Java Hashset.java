

        //Write your code here
        Set<List<String>> set = new HashSet<>();
        for (int i = 0; i < t; i++) {
            List<String> l = new ArrayList<>();
            l.add(pair_left[i]);
            l.add(pair_right[i]);
            set.add(l);
            System.out.println(set.size());
        }

