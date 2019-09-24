<template>
  <div>
    <b-field class="level" grouped>
      <p class="control">WiFi AP (Host)</p>
      <b-input
        class="control"
        :value="deviceSettings.hApName"
        expanded
        disabled
      ></b-input>
      <b-button type="is-primary" @click="isApModalActive = true"
        >Config
      </b-button>
    </b-field>

    <b-field class="level" grouped>
      <p class="control">WiFi AP (Client)</p>
      <b-input
        class="control"
        :value="deviceSettings.cApName || 'N/A'"
        expanded
        disabled
      ></b-input>
      <b-button type="is-primary" @click="isStaModalActive = true"
        >Config</b-button
      >
    </b-field>

    <b-field class="level" grouped>
      <p class="control">WiFi Mode</p>
      <b-select expanded :value="deviceSettings.wifiMode" disabled>
        <option v-for="v in wifiModes" :value="v.value" :key="v.label">
          {{ v.label }}
        </option>
      </b-select>
      <b-button type="is-primary" @click="isModeModalActive = true"
        >Config</b-button
      >
    </b-field>

    <b-modal :active.sync="isApModalActive" has-modal-card>
      <ap-modal></ap-modal>
    </b-modal>
    <b-modal :active.sync="isStaModalActive" has-modal-card>
      <sta-modal></sta-modal>
    </b-modal>
    <b-modal :active.sync="isModeModalActive" has-modal-card>
      <mode-modal></mode-modal>
    </b-modal>
  </div>
</template>

<script>
import { mapActions, mapState } from 'vuex';

import ApModal from './ApModal';
import StaModal from './StaModal';
import ModeModal from './ModeModal';

const wifiModes = [
  {
    label: 'AP (Host)',
    value: 2,
  },
  {
    label: 'STA (Client)',
    value: 1,
  },
  {
    label: 'AP+STA (Host+Client)',
    value: 3,
  },
];

export default {
  components: {
    ApModal,
    StaModal,
    ModeModal,
  },
  data() {
    return {
      isApModalActive: false,
      isStaModalActive: false,
      isModeModalActive: false,
      wifiModes,
    };
  },
  computed: {
    ...mapState(['deviceSettings']),
  },
  methods: {
    ...mapActions(['postDeviceSettings', 'fetchDeviceSettings']),
  },
};
</script>
